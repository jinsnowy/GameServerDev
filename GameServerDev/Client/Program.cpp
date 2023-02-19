#include "stdafx.h"

#include "ClientPacketHandler.h"
#include "NetworkManager.h"
#include "Protocol\ProtobufUtils.h"

using namespace std;
using namespace Core;
using namespace Core::System;
using namespace Core::Network;
using namespace Core::Network::Packet;
using namespace Core::Network::Session;
using namespace Core::Network::Service;

int main(int argc, char** argv)
{
    Core::Initialize();
    Core::Config::thread_count = 1;

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

    int packetNum = 0;

    while (1)
    {
        service->ForEach([&packetNum](SessionPtr session)
        {
           string narrow = ProtobufUtils::EncodeUtf16(L"안녕하세요 테스트 중입니다.");

            User::Test test;
            test.set_text(narrow);

            session->Send(test);
        });

        std::this_thread::sleep_for(100ms);

        ++packetNum;
    }

    return 0;
}