#include "pch.h"
#include "MessageQueue.h"
#include "Message.h"
#include "Actor.h"

#include "../ExecutionContext.h"

namespace Core {
	namespace System {
		namespace Actor {
			MessageQueue::MessageQueue()
				:
				_actor(nullptr)
			{
			}

			MessageQueue::~MessageQueue() {
				_message_container.clear();
			}

			int64_t MessageQueue::Flush()
			{
				Timer timer = Timer::startNew();

				Message* message = nullptr;
				while (_message_container.try_pop(message) && message)
				{
					message->Execute();

					delete message;
				}

				return static_cast<int64_t>(timer.Count<std::chrono::milliseconds>());
			}

			bool MessageQueue::Empty() {
				return _message_container.empty();
			}

			void MessageQueue::Enqueue(MessagePtr&& message) {
				_message_container.push(message.release());
			}

			void MessageQueue::Assign(std::shared_ptr<Actor> actor) {
				_actor = actor;
			}

			void MessageQueue::Enter(ExecutionContext* exec_context)
			{
				_actor->Enter(exec_context);
			}

			void MessageQueue::Leave()
			{
				_actor->Leave();
			}
		}
	}
}