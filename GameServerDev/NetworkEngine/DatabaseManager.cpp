#include "pch.h"
#include "DatabaseManager.h"

bool DatabaseManager::Initialize(const Config& config)
{
    return pool.Connect(config.connCount, config.connstr.c_str());
}

DBConnectionPtr DatabaseManager::GetConnection()
{
    return pool.GetConnection();
}

void DatabaseManager::Destroy()
{
    pool.Clear();
}
