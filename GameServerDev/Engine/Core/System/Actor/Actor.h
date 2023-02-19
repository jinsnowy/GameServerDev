#pragma once

#include "Message.h"

namespace Core {
	namespace System {
		class ExecutionContext;

		namespace Actor {
			class Message;
			class MessageQueue;
			class Actor : public enable_shared_from_this<Actor>
			{
				friend class MessageQueue;
			public:
				Actor();
				virtual ~Actor();

			public:
				template<typename R, typename T, typename ...Args>
				void Enqueue(const wchar_t* sig, R(T::* mem_func)(Args...), Args... args) {
					shared_ptr<T> obj = static_pointer_cast<T>(shared_from_this());
					Enqueue(MakeMessage(sig, mem_func, obj, std::forward<Args>(args)...));
				}

				template<typename T, typename F>
				void Enqueue(const wchar_t* sig, F&& then) {
					Enqueue(MakeMessage(sig, then, static_pointer_cast<T>(shared_from_this())));
				}

			private:
				ExecutionContext* _exec_context;
				atomic<int32_t> _entering_context_count;
				std::atomic<MessageQueue*> _message_queue;

			private:
				void Enqueue(MessagePtr&& message);

				void Enter(ExecutionContext* exec_context);
				void Leave();
			};
		}
	}
}

#define ENQUEUE_MEM(mem_func, ...) Enqueue(__FUNCTIONW__, mem_func, ##__VA_ARGS__)
#define ENQUEUE(T, then) Enqueue<T>(__FUNCTIONW__, then)