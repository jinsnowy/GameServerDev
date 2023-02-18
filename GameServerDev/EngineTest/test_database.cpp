#include "pch.h"
#include "Engine\Core\Database\DBUtils.h"

//class DatabaseTest : public ::testing::Test
//{
//public:
//	DatabaseTest() {
//		DatabaseManager::GetInstance().Initialize();
//	}
//
//	~DatabaseTest();
//};
//
//
//TEST_F(DatabaseTest, 우편_이벤트_삽입) {
//	auto db_conn = DatabaseManager::GetInstance().GetConnection();
//	db_conn->BeginTransaction();
//
//
//	auto stmt = db_conn->CreateStatement();
//
//	int16 event_type = 0;
//
//	stmt->BindParam(event_type);
//	stmt->BindParam(L"2019-01-02 12:00:00");
//	stmt->BindParam(L"2019-01-03 12:00:00");
//
//	db_conn->Rollback();
//}