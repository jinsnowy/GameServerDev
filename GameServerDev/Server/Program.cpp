#include "stdafx.h"
#include "Engine/Common/ServerCommon.h"

#include "Repository/AccountRepository.h"

#include "ServerPacketHandler.h"
#include "UserSession.h"
#include "Protocol/UserProtocol.pb.h"

using namespace std;
using namespace packet;

int main(int argc, char ** argv)
{
	Core::Initialize();
	Core::Config::thread_count = 4;

	GamePacketInstaller::Install<ServerPacketHandler>();
	

	SessionFactory sessionFactory = Session::CreateSessionFactory<UserSession>();
	NetworkFactory networkFactory = TcpNetwork::CreateFactory<ServerHandshake>();
	ServerServiceBuilder builder;

	auto service = builder
					.Sessions(sessionFactory)
					.Networks(networkFactory)
					.Build();

	service->RegisterRepository<AccountRepository>();
	service->Initialize();
	service->Start();
	service->RunIdle();

    return 0;
}
