#include "pch.h"
#include "Actor.h"
#include "Message.h"
#include "MessageQueue.h"

#include "../ExecutionContext.h"
#include "../GlobalWaitingQueue.h"

namespace Core {
	namespace System {
		namespace Actor {
			Actor::Actor()
				:
				_exec_context(nullptr),
				_message_queue(new MessageQueue()),
				_entering_context_count(0) {
			}

			Actor::~Actor() {
			}

			void Actor::Enqueue(MessagePtr&& message) {
				_entering_context_count.fetch_add(1);
				_message_queue.load()->Enqueue(std::move(message));

				if (_entering_context_count.fetch_sub(1) == 1) {
					auto scheduling_message_queue = _message_queue.exchange(new MessageQueue());
					scheduling_message_queue->Assign(shared_from_this());
					System::GlobalWaitingQueue::GetInstance().Schedule(scheduling_message_queue);
				}
			}

			void Actor::Enter(System::ExecutionContext* exec_context) {
				_exec_context = exec_context;
			}

			void Actor::Leave() {
				_exec_context = nullptr;
			}
		}
	}
}

