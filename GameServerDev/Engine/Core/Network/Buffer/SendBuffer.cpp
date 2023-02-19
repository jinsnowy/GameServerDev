#include "pch.h"
#include "SendBuffer.h"

namespace Core {
	namespace Network {
		namespace Buffer {
			SendBuffer::SendBuffer()
			{
			}

			SendBuffer::~SendBuffer()
			{
			}

			void SendBuffer::Pend(const BufferSegment& segment)
			{
				_writeData.Append(segment);
			}

			WriteData SendBuffer::Flush()
			{
				return std::move(_writeData);
			}

			void SendBuffer::Clear()
			{
				_writeData.Clear();
			}
		}
	}
}