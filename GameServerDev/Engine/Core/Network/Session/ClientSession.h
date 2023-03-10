#pragma once
#include "SessionBase.h"

namespace Core {
	namespace Network {
		namespace Session {
			class ClientSession : public SessionBase
			{
			public:
				ClientSession();

				bool Connect(const char* address, uint16 port);

				bool Connect(const EndPoint& endPoint);

				bool Reconnect(const EndPoint& endPoint);

				void ConnectAsync(const EndPoint& endPoint);

				void ReconnectAsync(const EndPoint& endPoint);

			protected:
				virtual void OnConnected() override;

				virtual void OnDisconnected() override;
			};
		}
	}
}