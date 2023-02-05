#pragma once

#include "Engine/Core/Network/Object/TcpNetwork.h"
#include "Engine/Core/Packet/PacketHandler.h"

class NetworkMock : public TcpNetwork
{
public:
	NetworkMock(ServiceBase& serviceBase);

	void SetConnectedMock();
	
	void SetDisconnectedMock();

	template <typename T>
	void RecvMock(const T& packet, packet::PacketHandler* handler) 
	{
		BufferSegment segment = Serializer::SerializeProtoBuf(packet);

		RecvBuffer& recvBuffer = TcpNetwork::GetRecvBuffer();
		SystemUtils::Copy(recvBuffer.GetBufferPtr(), recvBuffer.GetFreeSize(), segment.buf, static_cast<size_t>(segment.len));
		ASSERT_CRASH(recvBuffer.GetDataSize() == static_cast<size_t>(segment.len));
		TcpNetwork::Recv(recvBuffer.GetDataSize(), handler);
	}


	template <typename T>
	void RecvMock(const T& packet)
	{
		BufferSegment segment = Serializer::SerializeProtoBuf(packet);

		RecvBuffer& recvBuffer = TcpNetwork::GetRecvBuffer();
		SystemUtils::Copy(recvBuffer.GetBufferPtr(), recvBuffer.GetFreeSize(), segment.buf, static_cast<size_t>(segment.len));
		ASSERT_CRASH(recvBuffer.GetDataSize() == static_cast<size_t>(segment.len));
		TcpNetwork::Recv(recvBuffer.GetDataSize());
	}
};

