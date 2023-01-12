#include "pch.h"
#include "SendBuffer.h"

SendBuffer::SendBuffer()
{
}

SendBuffer::~SendBuffer()
{
}

void SendBuffer::Pend(const BufferSegment& segment)
{
	StdWriteLock lock(_sync);

	_writeData.Append(segment);
}

WriteData SendBuffer::Flush()
{
	StdWriteLock lock(_sync);

	return std::move(_writeData);
}

void SendBuffer::Clear()
{
	_writeData.Clear();
}
