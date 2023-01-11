#pragma once

class TcpNetwork;

struct RecvEvent
{
	shared_ptr<TcpNetwork> network;

	RecvEvent(shared_ptr<TcpNetwork> networkIn);

	void operator()(int32 errorCode, DWORD recvBytes);
};

struct SendEvent
{
	shared_ptr<TcpNetwork> network;
	std::vector<BufferSegment> segmentHolder;

	SendEvent(shared_ptr<TcpNetwork>  networkIn, std::vector<BufferSegment>&& segments);

	void operator()(int32 errorCode, DWORD writeBytes);
};

struct ConnectEvent
{
	shared_ptr<TcpNetwork> network;
	EndPoint endPoint;

	ConnectEvent(shared_ptr<TcpNetwork>  networkIn, EndPoint _endPoint);

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