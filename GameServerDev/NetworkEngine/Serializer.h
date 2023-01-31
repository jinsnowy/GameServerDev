#pragma once

class Serializer
{
public:
	template<typename T, typename = enable_if_t<is_base_of_v<PacketHeader, T>>>
	static BufferSegment SerializeStruct(const T& packet)
	{
		const_cast<T&>(packet).size = sizeof(T);
		return Sink((CHAR*)&packet, sizeof(T));
	}

	template<typename T>
	static BufferSegment SerializeProtoBuf(const T& pkt)
	{
		int pktLen = (int)pkt.ByteSizeLong();
		auto segment = SerializePacketHeader(packet::Protocol::GetProtocol<T>(), pktLen);

		if (!pkt.SerializeToArray(segment.buf + sizeof(PacketHeader), pktLen))
		{
			return BufferSegment(NULL, 0, NULL);
		}

		return segment;
	}

	static BufferSegment SerializePacketHeader(int32 protocol, int32 pktLen);

	static BufferSegment Sink(CHAR* data, int32 len);
};