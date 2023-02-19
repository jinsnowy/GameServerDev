#pragma once

#include "../Memory/PoolObject.h"

namespace Core {
	namespace System {
		namespace Actor {
			class Message : public Memory::PoolObject
			{
			private:
				const wchar_t* sig;
				std::function<void()> func;

			public:
				Message(const wchar_t* _sig, std::function<void()> _func) : sig(_sig), func(std::move(_func)) {}

				const wchar_t* GetTag() { return sig; }

				void operator()() { func(); }

				void Execute() { func(); }
			};

			template<typename F, typename T, size_t ...Is>
			static void __Call__(F&& func, T&& tupleArgs, std::index_sequence<Is...>) {
				std::invoke(std::forward<F>(func), std::get<Is>(tupleArgs)...);
			}

			static MessagePtr MakeMessage(const wchar_t* sig, std::function<void()> fIn) {
				return std::make_unique<Message>(sig, std::move(fIn));
			}

			template<typename F, typename ...Args>
			static MessagePtr MakeMessage(const wchar_t* sig, F&& fIn, Args&&... argsIn) {
				return std::make_unique<Message>(sig, [f = std::forward<F>(fIn), tupleArgs = std::make_tuple(std::forward<Args>(argsIn)...)]() mutable {
					using TupleType = decltype(tupleArgs);
					__Call__(f, tupleArgs, std::make_index_sequence<std::tuple_size_v<TupleType>>());
				});
			}

			template<typename R, typename C, typename ...A, typename ...Args>
			static MessagePtr MakeMessage(const wchar_t* sig, R(C::* mem_func)(A...), C* inst, Args&&... argsIn) {
				return std::make_unique<Message>(sig, [mem_func, tupleArgs = std::make_tuple(inst, std::forward<Args>(argsIn)...)]() mutable {
					using TupleType = decltype(tupleArgs);
					__Call__(mem_func, tupleArgs, std::make_index_sequence<std::tuple_size_v<TupleType>>());
				});
			}

			template<typename R, typename C, typename ...A, typename ...Args>
			static MessagePtr MakeMessage(const wchar_t* sig, R(C::* mem_func)(A...), const std::shared_ptr<C>& inst, Args&&... argsIn) {
				return std::make_unique<Message>(sig, [mem_func, tupleArgs = std::make_tuple(inst, std::forward<Args>(argsIn)...)]() mutable {
					using TupleType = decltype(tupleArgs);
					__Call__(mem_func, tupleArgs, std::make_index_sequence<std::tuple_size_v<TupleType>>());
				});
			}
		}
	}
}