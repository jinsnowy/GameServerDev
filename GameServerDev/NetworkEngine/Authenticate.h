#pragma once

class Authenticate
{
public:
	static void OnSuccessHandshake(NetworkPtr network);
	static void OnFailureHandshake(NetworkPtr network);
};

