#include "stdafx.h"
#include <crtdbg.h>
#include <TcpSocket.h>
#include <MemoryPool.h>

#include "GamePacketInstaller.h"
#include "ClientPacketHandler.h"
#include "ClientService.h"
#include "PlayerSession.h"
#include "SessionManager.h"

using namespace std;

int main(int argc, char** argv)
{
    NetUtils::Initialize();
    MemoryPool::Initialize();
    GamePacketInstaller::Install<ClientPacketHandler>();

    SessionFactory sessionFactory = Session::CreateSessionFactory<PlayerSession>();
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
                UserProtocol::TEST test;
                test.set_text(String::Format("[%d] hello world : %lld", packetNum, session->GetSessionId()));

                session->SendAsync(Serializer::SerializeProtoBuf(test));
            });

            std::this_thread::sleep_for(100ms);

            ++packetNum;
        }
    });

    return 0;
}