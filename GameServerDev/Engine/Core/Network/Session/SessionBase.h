#pragma once

#include "../../System/Actor/Actor.h"

namespace Core {
	namespace System {
		class ThreadContext;
	}
	namespace Network {
		namespace Buffer {
			struct BufferSegment;
		}
		namespace Packet {
			class PacketHandler;
			struct PacketHeader;
			class Serializer;
		}
		namespace Session {
			using BufferSegment = Buffer::BufferSegment;
			using PacketHandler = Packet::PacketHandler;
			using PacketHeader = Packet::PacketHeader;
			using Serializer = Packet::Serializer;

			class SessionBase : public System::Actor::Actor
			{
				friend class TcpNetwork;
				friend class TcpListener;
			public:
				SessionBase();

				virtual ~SessionBase();

			public:
				System::ThreadContext* GetContext();

				template<typename T>
				shared_ptr<T> GetShared() { return static_pointer_cast<T>(shared_from_this()); }

				template <typename T>
				requires std::is_copy_constructible_v<T>&& std::is_copy_assignable_v<T>
					void Send(const T& message) {
					if constexpr (std::is_same_v<BufferSegment, T>) {
						SendInternal(message);
					}
					else {
						SendInternal(Serializer::SerializeProtoBuf(message));
					}
				}

				bool IsConnected();

				void Disconnect();

				void DisconnectAsync();

				void HandleRecv(PacketHandler* handler, const PacketHeader& header, CHAR* buffer);

			protected:
				shared_ptr<TcpNetwork> _network;

				virtual void OnConnected();
				virtual void OnDisconnected();

				virtual void AttachNetwork(shared_ptr<TcpNetwork> network) sealed;
				virtual void DetachNetwork() sealed;

			public:
				EndPoint	 GetEndPoint();
				wstring		 GetEndPointDesc() { return GetEndPoint().ToString(); }
				NetworkPtr	 GetNetwork() { return _network; }

				SessionID	 GetSessionId() { return _sessionId; }
				void		 SetSessionId(SessionID sessionId) { _sessionId = sessionId; }

			private:
				SessionID _sessionId;

				void SendInternal(const BufferSegment& segment);
			};

			template<typename T, typename = enable_if_t<is_base_of_v<SessionBase, T>>>
			static SessionFactory CreateSessionFactory() {
				return []() { return SessionPtr(new T()); };
			}
		}
	}
}