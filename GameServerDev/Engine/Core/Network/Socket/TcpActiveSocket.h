#pragma once

#include "TcpSocket.h"
#include "../IO/IoEvent.h"
#include "../Object/TcpNetworkEvent.h"

namespace Core {
	namespace Network {
		namespace Socket {
			class TcpActiveSocket : public TcpSocket
			{
			public:
				TcpActiveSocket(Service::ServiceBase& service);

				template<typename AsyncIoCompleteRoutine>
				bool WriteAsync(char* buffer, DWORD len, AsyncIoCompleteRoutine&& callback)
				{
					IO::IoEvent* ioEvent = IO::MakeWriteTask(std::forward<AsyncIoCompleteRoutine>(callback));

					if (!NetUtils::WriteAsync(_socket, reinterpret_cast<LPWSAOVERLAPPED>(ioEvent), buffer, len))
					{
						ioEvent->release();
						return false;
					}

					return true;
				}

				template<typename AsyncIoCompleteRoutine>
				bool WriteAsync(vector<WSABUF> buffers, AsyncIoCompleteRoutine&& callback)
				{
					IO::IoEvent* ioEvent = IO::MakeWriteTask(std::forward<AsyncIoCompleteRoutine>(callback));

					if (!NetUtils::WriteAsync(_socket, reinterpret_cast<LPWSAOVERLAPPED>(ioEvent), buffers.data(), (DWORD)buffers.size()))
					{
						ioEvent->release();

						return false;
					}

					return true;
				}

				template<typename AsyncIoCompleteRoutine>
				bool ReadAsync(char* buffer, ULONG len, AsyncIoCompleteRoutine&& callback)
				{
					IO::IoEvent* ioEvent = IO::MakeReadTask(std::forward<AsyncIoCompleteRoutine>(callback));

					if (!NetUtils::ReadAsync(_socket, reinterpret_cast<LPWSAOVERLAPPED>(ioEvent), buffer, len))
					{
						ioEvent->release();

						return false;
					}

					return true;
				}

				template<typename AsyncIoCompleteRoutine>
				bool ConnectAsync(const EndPoint& endPoint, AsyncIoCompleteRoutine&& callback)
				{
					IO::IoEvent* ioEvent = IO::MakeConnectTask(std::forward<AsyncIoCompleteRoutine>(callback));

					if (!NetUtils::ConnectAsync(_socket, reinterpret_cast<LPWSAOVERLAPPED>(ioEvent), endPoint))
					{
						ioEvent->release();

						return false;
					}

					return true;
				}

				template<typename AsyncIoCompleteRoutine>
				bool DisconnectAsync(AsyncIoCompleteRoutine&& callback)
				{
					IO::IoEvent* ioEvent = IO::MakeDisconnectTask(std::forward<AsyncIoCompleteRoutine>(callback));

					if (!NetUtils::DisconnectAsync(_socket, reinterpret_cast<LPWSAOVERLAPPED>(ioEvent)))
					{
						ioEvent->release();

						return false;
					}

					return true;
				}
			};
		}
	}
}