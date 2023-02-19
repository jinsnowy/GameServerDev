#pragma once

#ifndef UE_INCLUDE
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;
#endif

typedef uint64 SessionID;

namespace Core {
	namespace System {
		namespace Actor {
			class Message;
			class MessageQueue;
		}
	}

	namespace Network {
		class TcpNetwork;
		class TcpListener;
		class Handshake;
		namespace Buffer {
			class BufferSource;
		}
		namespace Session {
			class SessionBase;
		}
		namespace Service {
			class ServiceBase;
		}
	}

	using BufferSourcePtr = shared_ptr<Network::Buffer::BufferSource>;
	using SessionPtr = std::shared_ptr<Network::Session::SessionBase>;
	using SessionWeakPtr = std::weak_ptr<Network::Session::SessionBase>;
	using SessionPtrCRef = const SessionPtr&;

	using ListenerPtr = std::shared_ptr<Network::TcpListener>;
	using SessionFactory = std::function<SessionPtr()>;

	using NetworkPtr = std::shared_ptr<Network::TcpNetwork>;
	using NetworkPtrCRef = const std::shared_ptr<Core::Network::TcpNetwork>&;
	using MessagePtr = std::unique_ptr<System::Actor::Message>;
	using MessageQueuePtr = std::unique_ptr<System::Actor::MessageQueue>;

	using NetworkFactory = std::function<NetworkPtr(Network::Service::ServiceBase&)>;
	using OnAcceptFunc = std::function<bool(NetworkPtr)>;
	using OnConnectFunc = std::function<void(NetworkPtr)>;
	using OnConnectFailFunc = std::function<void(int)>;

	using PacketHandlerFunc = std::function<void(SessionPtr)>;
	using HandshakePtr = std::unique_ptr<Network::Handshake>;
}

static const char* get_bool_str(const bool& v) { return v ? "true" : "false"; }
