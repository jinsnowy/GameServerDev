#include "pch.h"
#include "GlobalWaitingQueue.h"
#include "Actor/MessageQueue.h"
#include "Memory/MemoryPool.h"

namespace Core {
	namespace System {
		GlobalWaitingQueue::GlobalWaitingQueue() {
		}

		GlobalWaitingQueue::~GlobalWaitingQueue() {
		}

		void GlobalWaitingQueue::Schedule(Actor::MessageQueue* message_queue) {
			_schedule_queue.push(message_queue);
		}

		bool GlobalWaitingQueue::Fetch(MessageQueuePtr& message_queue) {
			Actor::MessageQueue* message_queue_ptr = nullptr;
			if (_schedule_queue.try_pop(message_queue_ptr)) {
				message_queue.reset(message_queue_ptr);
				return true;
			}

			return false;
		}
	}
}