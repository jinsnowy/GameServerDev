#pragma once

#include "../Memory/PoolObject.h"

namespace Core {
	namespace System {
		class ExecutionContext;
		namespace Actor {
			class Actor;
			class Message;
			class MessageQueue : public Memory::PoolObject
			{
				friend class TaskScheduler;
			public:
				std::shared_ptr<Actor> _actor;
				concurrency::concurrent_queue<Message*> _message_container;

			public:
				MessageQueue();
				~MessageQueue();

				void Enqueue(MessagePtr&& message);
				void Assign(std::shared_ptr<Actor> actor);

				void Enter(ExecutionContext* exec_context);
				void Leave();

				int64_t Flush();
				bool Empty();
			};
		}
	}
}