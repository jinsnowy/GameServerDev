#include "stdafx.h"

#include "ServerPacketHandler.h"
#include "UserSession.h"
#include "Room.h"

#include "Protocol/UserProtocol.pb.h"

#include "Engine/Core/Packet/GamePacketInstaller.h"
#include "Engine/Core/Network/Object/TcpListener.h"
#include "Engine/Core/Service/ServerService.h"
#include "Engine/Core/Session/ServerSession.h"
#include "Engine/Core/Session/SessionManager.h"
#include "Engine/Core/Task/TaskScheduler.h"
#include "Engine/GlobalConfig.h"
#include "Engine/Database/DatabaseManager.h"

using namespace std;
using namespace packet;

static void Process();

int main(int argc, char ** argv)
{
    NetUtils::Initialize();
    MemoryPool::Initialize();

	DatabaseManager db;
	DatabaseManager::Config config;
	config.connCount = 1;
	config.connstr = global::SqlConnString;
	ASSERT_CRASH(db.Initialize(config));

   // bool result = DBConnectionPool::GetInstance()->Connect(1, connString);
   // 
   // {
   //     auto query = L"									\
			//DROP TABLE IF EXISTS [dbo].[Gold];			\
			//CREATE TABLE [dbo].[Gold]					\
			//(											\
			//	[id] INT NOT NULL PRIMARY KEY IDENTITY, \
			//	[gold] INT NULL,						\
			//	[name] NVARCHAR(50) NULL,				\
			//	[createDate] DATETIME NULL				\
			//);";

   //     DBConnection* dbConn = DBConnectionPool::GetInstance()->Pop();
   //     ASSERT_CRASH(dbConn->Execute(query));
   //     DBConnectionPool::GetInstance()->Push(dbConn);
   // }
   // 
   // // Add Data
   // for (int32 i = 0; i < 3; ++i)
   // {
   //     DBConnection* dbConn = DBConnectionPool::GetInstance()->Pop();

   //     DBBind<3, 0> dbBind(*dbConn, L"INSERT INTO [dbo].[Gold]([gold], [name], [createDate]) VALUES(?, ?, ?)");
   //     
   //     int32 gold = 100;
   //     dbBind.BindParam(0, gold);
   //     WCHAR name[100] = L"---";
   //     dbBind.BindParam(1, name);
   //     TIMESTAMP_STRUCT ts = { 2021, 6, 5 };
   //     dbBind.BindParam(2, ts);

   //     ASSERT_CRASH(dbBind.Execute());

   //     DBConnectionPool::GetInstance()->Push(dbConn);
   // }

   // // Read
   // {
   //     DBConnection* dbConn = DBConnectionPool::GetInstance()->Pop();

   //     dbConn->Unbind();

   //     DBBind<1, 4> dbBind(*dbConn, L"SELECT id, gold, name, createDate FROM [dbo].[Gold] WHERE gold = (?)");

   //     int32 gold = 100;
   //     dbBind.BindParam(0, gold);

   //     int32 outId = 0;
   //     int32 outGold = 0;
   //     WCHAR outName[100] = {};
   //     TIMESTAMP_STRUCT outDate = {};
   //     dbBind.BindCol(0, OUT outId);
   //     dbBind.BindCol(1, OUT outGold);
   //     dbBind.BindCol(2, OUT outName);
   //     dbBind.BindCol(3, OUT outDate);

   //     ASSERT_CRASH(dbBind.Execute());

   //     while (dbBind.Fetch())
   //     {
   //        LOG_INFO("id : %d, Gold : %d, Name : %s, Date : %d/%d/%d", outId, outGold, Format::toNarrow(outName).c_str(), (int)outDate.year, (int)outDate.month, (int)outDate.day);
   //     }

   //     DBConnectionPool::GetInstance()->Push(dbConn);
   // }

	GamePacketInstaller::Install<ServerPacketHandler>();

	SessionFactory sessionFactory = Session::CreateSessionFactory<UserSession>();
	SessionManager sessionManager(sessionFactory);

	ServerServiceParam param(12321, 10);
	ServerService service(sessionManager, param);
	service.Start();
	service.Run(Process);

    return 0;
}

void Process()
{
    while (true)
    {
        std::this_thread::sleep_for(5s);
    }
}