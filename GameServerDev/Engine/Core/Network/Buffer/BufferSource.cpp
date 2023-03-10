#include "pch.h"
#include "BufferSource.h"
#include "Core/Network/Packet/PacketHeader.h"

namespace Core {
	namespace Network {
		namespace Buffer {
			BufferSourcePtr BufferSource::GetBuffer(int32 len)
			{
				ASSERT_CRASH(len <= BUFFER_SIZE);

				thread_local queue<BufferSourcePtr> bufferQue;

				if (bufferQue.empty())
				{
					bufferQue.push(Make());
				}

				auto buffer = bufferQue.front();
				if (buffer->enough(len) == false)
				{
					bufferQue.pop(); bufferQue.push(Make());
					buffer = bufferQue.front();
				}

				return buffer;
			}
		}
	}
}
