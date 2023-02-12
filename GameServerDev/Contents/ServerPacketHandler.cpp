#include "pch.h"
#include "ServerPacketHandler.h"

#include "Engine/Core/Service/ServiceBase.h"
#include "Engine/Core/Session/Session.h"
#include "Repository/AccountRepository.h"
#include "Engine/Utils/Crypto.h"

using namespace packet;

void ServerPacketHandler::onHeartbeat(SessionPtrCRef session, UserProtocol::Heartbeat pkt)
{
}

void ServerPacketHandler::onTest(SessionPtrCRef session, UserProtocol::Test pkt)
{
}

void ServerPacketHandler::onCreateAccountRequest(SessionPtrCRef session, UserProtocol::CreateAccountRequest pkt)
{
	auto repository = session->GetContext()->GetRepository<AccountRepository>();
	auto dbConn = session->GetContext()->GetDBConn();

	auto username = StringUtils::ToWide(pkt.username());
	auto password = StringUtils::ToWide(pkt.password());

	auto password_hash = Crypto::GenerateSHA256Hash(password);

	auto entity = repository->CreateNewAccount(dbConn, username, password_hash);

	UserProtocol::LoginResponse res;
	if (entity == nullptr) {
		res.set_result(UserProtocol::LoginResponse::kFailure);
	}
	else {
		res.set_result(UserProtocol::LoginResponse::kSuccess);
	}

	session->Send(res);
}

void ServerPacketHandler::onLoginRequest(SessionPtrCRef session, UserProtocol::LoginRequest pkt)
{
}
