#include "pch.h"
#include "Config.h"

std::wstring Core::Config::dbsn = L"Driver={ODBC Driver 17 for SQL Server};Server=DESKTOP-5DKI3L6;Trusted_Connection=Yes;Database=GameDB;";

int32 Core::Config::thread_count = std::thread::hardware_concurrency();

uint16 Core::Config::default_port = 9190;