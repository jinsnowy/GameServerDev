#include "pch.h"
#include "NetworkStream.h"

namespace Core {
	namespace Network {
		namespace Buffer {
			NetworkStream::NetworkStream()
			{
			}

			NetworkStream::~NetworkStream()
			{
			}

			void NetworkStream::Clear()
			{
				_recvBuffer.Clear();
				_sendBuffer.Clear();
			}

			bool NetworkStream::WriteDataExists()
			{
				return _sendBuffer.IsEmpty() == false;
			}

			void NetworkStream::Pend(const BufferSegment& segment)
			{
				_sendBuffer.Pend(segment);
			}

			WriteData NetworkStream::Flush()
			{
				return  _sendBuffer.Flush();
			}
		}
	}
}