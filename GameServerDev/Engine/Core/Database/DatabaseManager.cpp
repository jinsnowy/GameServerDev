#include "pch.h"
#include "DatabaseManager.h"
#include "Core/Common/Config.h"

DatabaseManager::DatabaseManager()
    :
    _initialized(false)
{
}

void DatabaseManager::Initialize()
{
    _initialized = false;

    if (pool.Connect(Core::Config::thread_count, Core::Config::dbsn.c_str()) == false)
    {
        throw std::runtime_error("db connection failed");
    }

    _initialized = true;
}

DBConnection* DatabaseManager::GetConnection()
{
    return pool.GetConnection();
}

void DatabaseManager::Destroy()
{
    pool.Clear();
}

bool DatabaseManager::IsInitialized()
{
    return _initialized;
}
