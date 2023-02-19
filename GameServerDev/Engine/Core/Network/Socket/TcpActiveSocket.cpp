#include "pch.h"
#include "TcpActiveSocket.h"

namespace Core {
	namespace Network {
		namespace Socket {
			TcpActiveSocket::TcpActiveSocket(Service::ServiceBase& service)
				:
				TcpSocket(service)
			{
			}
		}
	}
}