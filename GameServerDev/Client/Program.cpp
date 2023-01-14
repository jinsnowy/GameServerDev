#include "stdafx.h"
#include <crtdbg.h>
#include <TcpSocket.h>
#include <MemoryPool.h>

#include "GamePacketInstaller.h"
#include "ClientPacketHandler.h"
#include "ClientService.h"
#include "PlayerSession.h"

using namespace std;

int main(int argc, char** argv)
{
    NetUtils::Initialize();
    MemoryPool::Initialize();
    GamePacketInstaller::Install<ClientPacketHandler>();

    ClientSessionFactory sessionFactory = [](ServiceBase& serviceBase) { return shared_ptr<ClientSession>(new PlayerSession(serviceBase)); };
    ClientServiceParam param(20, 1, "127.0.0.1", 12321, sessionFactory);
    ClientService service(param);
    service.Start();
    service.Run([&]() 
    {
        while (1)
        {
            UserProtocol::TEST test;
            test.set_text("hello world!");

            service.Broadcast(Serializer::SerializeProtoBuf(test));

            std::this_thread::sleep_for(1s);
        }
    });

    return 0;
}