#pragma once

#include "Memory/MemoryPool.h"

namespace Core {
	namespace Actor {
		class MessageQueue;
	}
	namespace System {
		class GlobalWaitingQueue : public ISingleton<GlobalWaitingQueue>
		{
		public:
			GlobalWaitingQueue();
			~GlobalWaitingQueue();

			void Schedule(Actor::MessageQueue* message_queue);
			bool Fetch(MessageQueuePtr& message_queue);

		private:
			concurrency::concurrent_queue<Actor::MessageQueue*> _schedule_queue;
		};
	}
}