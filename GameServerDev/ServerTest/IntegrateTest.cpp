#include "pch.h"
#include "IntegrateTest.h"
#include "Engine/Common/ServerCommon.h"
#include "Contents/ServerPacketHandler.h"

IntegrateTest::IntegrateTest()
{
}

IntegrateTest::~IntegrateTest()
{
}

void IntegrateTest::SetUp()
{
	Core::Initialize();
	Core::Config::thread_count = 1;

	_serverMock.Initialize();
	_clientMock.Initialize();

	_serverMock.SetClient(_clientMock.GetNetworkMock());
	_clientMock.SetServer(_serverMock.GetNetworkMock());
}

void IntegrateTest::TearDown()
{
}