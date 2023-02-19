#pragma once

#include "../Buffer/BufferSegment.h"
#include "../Protocol/Protocol.h"
#include "../Packet/PacketHeader.h"

namespace Core {
	namespace Network {
		namespace Buffer {
			struct BufferSegment;
		}
		namespace Packet {
			class Serializer
			{
			public:
				template<typename T, typename = enable_if_t<is_base_of_v<PacketHeader, T>>>
				static Buffer::BufferSegment SerializeStruct(const T& packet)
				{
					const_cast<T&>(packet).size = sizeof(T);
					return Sink((CHAR*)&packet, sizeof(T));
				}

				template<typename T>
				static Buffer::BufferSegment SerializeProtoBuf(const T& pkt)
				{
					int pktLen = (int)pkt.ByteSizeLong();
					auto segment = SerializePacketHeader(Protocol::TypeCode::Get<T>(), pktLen);

					if (!pkt.SerializeToArray(segment.buf + sizeof(PacketHeader), pktLen))
					{
						return Buffer::BufferSegment(NULL, 0, NULL);
					}

					return segment;
				}

				static Buffer::BufferSegment SerializePacketHeader(int32 protocol, int32 pktLen);

				static Buffer::BufferSegment Sink(CHAR* data, int32 len);
			};
		}
	}
}