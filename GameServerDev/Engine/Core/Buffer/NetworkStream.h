#pragma once

#include "BufferSegment.h"
#include "RecvBuffer.h"
#include "SendBuffer.h"

class NetworkStream
{
private:
	RecvBuffer				_recvBuffer;
	SendBuffer				_sendBuffer;

public:
	NetworkStream();
	~NetworkStream();

	RecvBuffer& Recv() { return _recvBuffer; }
	
	SendBuffer& Send() { return _sendBuffer; }

	void Clear();

	bool WriteDataExists();

	void Pend(const BufferSegment& segment);

	WriteData Flush();
};

