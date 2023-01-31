#include "pch.h"
#include "Serializer.h"

BufferSegment Serializer::SerializePacketHeader(int32 protocol, int32 pktLen)
{
	int32 len = pktLen + sizeof(packet::PacketHeader);

	auto buffer = BufferSource::GetBuffer(len);

	CHAR* buf = buffer->lend(len);

	packet::PacketHeader header = packet::PacketHeader(protocol, len);

	memcpy(buf, &header, sizeof(packet::PacketHeader));

	return BufferSegment(buf, len, buffer);
}

BufferSegment Serializer::Sink(CHAR* data, int32 len)
{
	auto buffer = BufferSource::GetBuffer(len);

	CHAR* buf = buffer->copy(data, len);

	return BufferSegment(buf, (ULONG)len, buffer);
}
