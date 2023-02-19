#include "pch.h"
#include "TcpSocket.h"
#include "Core/Network/Service/ServiceBase.h"
#include "Core/Network/IO/IoContext.h"
#include "Core/System/ThreadContext.h"

namespace Core {
	namespace Network {
		namespace Socket {
			TcpSocket::TcpSocket(ServiceBase& service)
				:
				_service(service),
				_socket(NetUtils::CreateSocket())
			{
				_service.GetContext().GetIoContext()->RegisterHandle((HANDLE)_socket);
			}

			TcpSocket::~TcpSocket()
			{
				Dispose();
			}

			bool TcpSocket::SetLinger(uint16 onoff, uint16 linger)
			{
				return NetUtils::SetLinger(_socket, onoff, linger);
			}

			bool TcpSocket::SetReuseAddress(bool flag)
			{
				return NetUtils::SetReuseAddress(_socket, flag);
			}

			bool TcpSocket::SetRecvBufferSize(int32 size)
			{
				return NetUtils::SetRecvBufferSize(_socket, size);
			}

			bool TcpSocket::SetSendBufferSize(int32 size)
			{
				return NetUtils::SetSendBufferSize(_socket, size);
			}

			bool TcpSocket::SetTcpNoDelay(bool flag)
			{
				return NetUtils::SetTcpNoDelay(_socket, flag);
			}

			bool TcpSocket::IsOk()
			{
				return NetUtils::IsOk(_socket);
			}

			void TcpSocket::Dispose()
			{
				if (_disposed.exchange(true) == false)
				{
					NetUtils::Close(_socket);
				}
			}

			void TcpSocket::Close()
			{
				NetUtils::Shutdown(_socket, SD_BOTH);
			}

			bool TcpSocket::IsDisposed()
			{
				return _disposed;
			}
		}
	}
}