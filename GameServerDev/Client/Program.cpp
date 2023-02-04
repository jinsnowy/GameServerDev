#include "stdafx.h"

#include "Engine/Core/Packet/GamePacketInstaller.h"
#include "Engine/Core/Service/ClientService.h"
#include "Engine/Core/Session/SessionManager.h"

#include "ClientPacketHandler.h"
#include "NetworkManager.h"

using namespace std;
using namespace packet;

int main(int argc, char** argv)
{
    Core::Initialize();
    GamePacketInstaller::Install<ClientPacketHandler>();

    SessionFactory sessionFactory = Session::CreateSessionFactory<NetworkManager>();
    SessionManager sessionManager(sessionFactory);

    ClientServiceParam param(1, 1, "127.0.0.1", 12321);
    ClientService service(sessionManager, param);
    service.Start();
    service.Run([&]() 
    {     
        int packetNum = 0;

        while (1)
        {
            service.ForEach([&packetNum](SessionPtr session)
            {            
                UserProtocol::Test test;
                test.set_text(StringUtils::Format("[%d] hello world : %lld", packetNum, session->GetSessionId()));

                session->SendAsync(Serializer::SerializeProtoBuf(test));
            });

            std::this_thread::sleep_for(100ms);

            ++packetNum;
        }
    });

    return 0;
}