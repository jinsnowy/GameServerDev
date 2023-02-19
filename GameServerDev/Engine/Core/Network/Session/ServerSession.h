#pragma once
#include "SessionBase.h"

namespace Core {
	namespace Network {
		namespace Session {
			class ServerSession : public SessionBase
			{
			public:
				ServerSession();

			protected:
				virtual void OnConnected() override;

				virtual void OnDisconnected() override;
			};
		}
	}
}