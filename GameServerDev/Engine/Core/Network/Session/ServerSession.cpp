#include "pch.h"
#include "ServerSession.h"

namespace Core {
	namespace Network {
		namespace Session {
			ServerSession::ServerSession()
				:
				SessionBase()
			{
			}

			void ServerSession::OnConnected()
			{
				SessionBase::OnConnected();
			}

			void ServerSession::OnDisconnected()
			{
				SessionBase::OnDisconnected();
			}
		}
	}
}