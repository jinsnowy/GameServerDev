#pragma once

namespace Core {
	namespace Network {
		class TcpNetwork;
		namespace Buffer {
			struct BufferSegment;
		}

		struct RecvEvent
		{
			shared_ptr<TcpNetwork> network;

			RecvEvent(shared_ptr<TcpNetwork> networkIn);

			void operator()(int32 errorCode, DWORD recvBytes);
		};

		struct SendEvent
		{
			shared_ptr<TcpNetwork> network;
			std::vector<Buffer::BufferSegment> segmentHolder;

			SendEvent(shared_ptr<TcpNetwork>  networkIn, std::vector<Buffer::BufferSegment>&& segments);

			void operator()(int32 errorCode, DWORD writeBytes);
		};

		struct ConnectEvent
		{
			shared_ptr<TcpNetwork> network;

			EndPoint endPoint;
			OnConnectFunc onConnected;
			OnConnectFailFunc onConnectFailed;

			ConnectEvent(shared_ptr<TcpNetwork> networkIn, EndPoint _endPoint, OnConnectFunc _onConnected, OnConnectFailFunc _onConnectFailed);

			void operator()(int32 errorCode, DWORD);
		};

		struct DisconnectEvent
		{
			shared_ptr<TcpNetwork> network;

			DisconnectEvent(shared_ptr<TcpNetwork> networkIn);

			void operator()(int32 errorCode, DWORD);
		};

		struct AcceptEvent
		{
			shared_ptr<TcpListener> listenerPtr;
			shared_ptr<TcpNetwork> networkPtr;

			AcceptEvent(shared_ptr<TcpListener> _listenerPtr, shared_ptr<TcpNetwork> _networkPtr);

			void operator()(int32 errorCode, DWORD);
		};
	}
}