#include "pch.h"
#include "DatabaseManager.h"
#include "DBConnectionSource.h"

bool DatabaseManager::Initialize(const Config& config)
{
    return pool.Connect(config.connCount, config.connstr.c_str());
}

std::shared_ptr<DBConnectionSource>  DatabaseManager::GetConnection()
{
    return pool.GetConnection();
}

void DatabaseManager::Destroy()
{
    pool.Clear();
}
