#include "pch.h"
#include "ExecutionContext.h"
#include "Actor/MessageQueue.h"
#include "GlobalWaitingQueue.h"

#include "../Common/Config.h"

namespace Core {
	namespace System {
		ExecutionContext::ExecutionContext()
		{
		}

		ExecutionContext::~ExecutionContext()
		{
		}

		void ExecutionContext::Execute(int64& time_slice)
		{
			MessageQueuePtr message_queue;
			if (GlobalWaitingQueue::GetInstance().Fetch(message_queue) == false) {
				return;
			}

			message_queue->Enter(this);

			time_slice -= message_queue->Flush();

			message_queue->Leave();

			if (message_queue->Empty() == false) {
				GlobalWaitingQueue::GetInstance().Schedule(message_queue.release());
			}
		}
	}
}