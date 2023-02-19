#include "pch.h"
#include "Serializer.h"
#include "Core/Network/Buffer/BufferSource.h"

namespace Core {
	namespace Network {
		namespace Packet {
			using namespace Buffer;

			Buffer::BufferSegment Serializer::SerializePacketHeader(int32 protocol, int32 pktLen)
			{
				int32 len = pktLen + sizeof(Packet::PacketHeader);

				auto buffer = BufferSource::GetBuffer(len);

				CHAR* buf = buffer->lend(len);

				Packet::PacketHeader header = Packet::PacketHeader(protocol, len);

				memcpy(buf, &header, sizeof(Packet::PacketHeader));

				return BufferSegment(buf, len, buffer);
			}

			Buffer::BufferSegment Serializer::Sink(CHAR* data, int32 len)
			{
				auto buffer = BufferSource::GetBuffer(len);

				CHAR* buf = buffer->copy(data, len);

				return BufferSegment(buf, (ULONG)len, buffer);
			}
		}
	}
}