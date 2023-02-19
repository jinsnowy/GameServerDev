#pragma once

namespace Core {
	namespace Network {
		namespace Service {
			class ServiceBase;
		}
		namespace IO {
			enum class IoType;
			struct IoEvent;
		}

		namespace Socket {
			class TcpSocket
			{
				friend class Service::ServiceBase;
				friend class TcpListenerSocket;

				using ServiceBase = Service::ServiceBase;
			protected:
				SOCKET	   _socket;

			private:
				ServiceBase& _service;
				atomic<bool> _disposed;

			public:
				TcpSocket(Service::ServiceBase& service);
				virtual ~TcpSocket();

				ServiceBase& Service() { return _service; }
				SOCKET   GetSocket() { return _socket; }

				bool SetLinger(uint16 onoff, uint16 linger);
				bool SetReuseAddress(bool flag);
				bool SetRecvBufferSize(int32 size);
				bool SetSendBufferSize(int32 size);
				bool SetTcpNoDelay(bool flag);

				bool IsOk();
				void Dispose();
				bool IsDisposed();
				void Close();
			};
		}
	}
}