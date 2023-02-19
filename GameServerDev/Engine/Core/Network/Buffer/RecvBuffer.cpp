#include "pch.h"
#include "RecvBuffer.h"
#include "Core/Network/Packet/PacketHeader.h"

namespace Core {
	namespace Network {
		namespace Buffer {
			RecvBuffer::RecvBuffer()
			{
				ZeroMemory(_buffer, sizeof(_buffer));
				_readPos = 0;
				_writePos = 0;
			}

			void RecvBuffer::Clear()
			{
				_readPos = _writePos = 0;
			}

			void RecvBuffer::Next()
			{
				if (_writePos == _readPos)
				{
					_writePos = _readPos = 0;
					return;
				}

				int32 dataSize = _writePos - _readPos;
				memcpy(&_buffer[0], &_buffer[_readPos], dataSize);
				_readPos = 0;
				_writePos = dataSize;
			}

			bool RecvBuffer::Read(int32 recvBytes)
			{
				if (isFree(recvBytes) == false)
					return false;

				_writePos += recvBytes;
				return true;
			}

			void RecvBuffer::Move(int32 readBytes)
			{
				_readPos += readBytes;
			}

			bool RecvBuffer::IsHeaderReadable()
			{
				return _writePos - _readPos >= sizeof(Packet::PacketHeader);
			}
		}
	}
}