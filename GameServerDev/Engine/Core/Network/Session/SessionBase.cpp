#include "pch.h"
#include "SessionBase.h"
#include "SessionManager.h"

#include "Core/Network/Buffer/NetworkStream.h"
#include "Core/Network/Buffer/BufferSegment.h"
#include "Core/Network/Object/TcpNetwork.h"
#include "Core/Network/Service/ServiceBase.h"
#include "Core/Network/Packet/PacketHandler.h"

namespace Core {
	namespace Network {
		namespace Session {
			SessionBase::SessionBase()
				:
				_sessionId(INVALID_SESSION_VALUE)
			{
			}

			SessionBase::~SessionBase()
			{
				LOG_INFO(L"~SessionBase()");
			}

			void SessionBase::SendInternal(const BufferSegment& segment)
			{
				if (IsConnected() == false || segment.len == 0)
					return;

				_network->SendAsync(segment);
			}

			System::ThreadContext* SessionBase::GetContext()
			{
				if (_network == nullptr) {
					return nullptr;
				}

				return &_network->AssociateService().GetContext();
			}

			void SessionBase::AttachNetwork(shared_ptr<TcpNetwork> network)
			{
				if (_network != nullptr && _network->IsConnected())
				{
					_network->CloseBy(L"attach new network");
					_network = nullptr;
				}

				_network = network;

				if (_network && _network->IsConnected())
				{
					OnConnected();
				}
			}

			void SessionBase::DetachNetwork()
			{
				if (_network)
				{
					OnDisconnected();
				}

				_network = nullptr;
			}

			bool SessionBase::IsConnected()
			{
				return _network != nullptr && _network->IsConnected();
			}

			void SessionBase::Disconnect()
			{
				if (_network == nullptr || _network->IsConnected() == false)
					return;

				_network->DisconnectAsync();

				int count = 0;
				while (IsConnected() && ++count < 10)
				{
					std::this_thread::sleep_for(100ms);
				}
			}

			void SessionBase::DisconnectAsync()
			{
				if (_network == nullptr || _network->IsConnected() == false)
					return;

				_network->DisconnectAsync();
			}

			void SessionBase::HandleRecv(PacketHandler* handler, const PacketHeader& header, CHAR* buffer)
			{
				CHAR* buffer_ptr = static_cast<CHAR*>(ALLOC(header.size));
				memcpy_s(buffer_ptr, header.size, buffer, header.size);
				Enqueue<SessionBase>(__FUNCTIONW__, [handler, header = header, buffer_ptr](SessionPtrCRef session) mutable {
					handler->HandleRecv(session, header, buffer_ptr);
					DEALLOC(buffer_ptr);
				});
			}

			void SessionBase::OnConnected()
			{
				static atomic<SessionID> sessionIDGen = 1;

				SetSessionId(sessionIDGen.fetch_add(1));

				LOG_INFO(L"sessionId %lld connected to %s", GetSessionId(), GetEndPointDesc().c_str());
			}

			void SessionBase::OnDisconnected()
			{
				LOG_INFO(L"disconnected from %s", GetEndPointDesc().c_str());
			}

			EndPoint SessionBase::GetEndPoint()
			{
				return _network != nullptr ? _network->GetEndPoint() : EndPoint();
			}
		}
	}
}