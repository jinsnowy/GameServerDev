#include "pch.h"
#include "Serializer.h"

BufferSegment Serializer::SerializePacketHeader(int32 protocol, int32 pktLen)
{
	int32 len = pktLen + sizeof(PacketHeader);

	auto buffer = BufferSource::GetBuffer(len);

	CHAR* buf = buffer->lend(len);

	PacketHeader header = PacketHeader(protocol, len);

	memcpy(buf, &header, sizeof(PacketHeader));

	return BufferSegment(buf, len, buffer);
}

BufferSegment Serializer::Sink(CHAR* data, int32 len)
{
	auto buffer = BufferSource::GetBuffer(len);

	CHAR* buf = buffer->copy(data, len);

	return BufferSegment(buf, (ULONG)len, buffer);
}
