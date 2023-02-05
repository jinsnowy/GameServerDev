#include "stdafx.h"

#include "Engine/Common/ClientCommon.h"
#include "ClientPacketHandler.h"
#include "NetworkManager.h"

using namespace std;
using namespace packet;

int main(int argc, char** argv)
{
    Core::Initialize();

    Config::thread_count = 1;

    GamePacketInstaller::Install<ClientPacketHandler>();

    SessionFactory sessionFactory = Session::CreateSessionFactory<NetworkManager>();
    NetworkFactory networkFactory = TcpNetwork::CreateFactory<ClientHandshake>();
    ClientServiceBuilder builder;

    auto service =  builder
                    .ClientNum(1)
                    .Sessions(sessionFactory)
                    .Networks(networkFactory)
                    .Build();

    service->Initialize();
    service->Start();
    service->Run([&]() 
    {     
        int packetNum = 0;

        while (1)
        {
            service->ForEach([&packetNum](SessionPtr session)
            {            
                UserProtocol::Test test;
                test.set_text(StringUtils::Format("[%d] hello world : %lld", packetNum, session->GetSessionId()));

                session->Send(test);
            });

            std::this_thread::sleep_for(100ms);

            ++packetNum;
        }
    });

    return 0;
}