#pragma once
#include "PacketHeader.h"
#include "Protocol.h"

struct BufferSegment : WSABUF
{
	BufferSourcePtr source;

	WSABUF AsBufffer() const { return WSABUF{ len, buf }; }

	BufferSegment(CHAR* _buf, ULONG _len, const BufferSourcePtr& _ptr) : WSABUF{ _len, _buf }, source(_ptr) {}
};
