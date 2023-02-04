#pragma once

class RecvBuffer
{
	enum
	{
		BUFFER_SIZE = 4096
	};
public:
	RecvBuffer();
	NO_COPY_AND_ASSIGN(RecvBuffer);

	CHAR* GetBufferPtr() { return &_buffer[_writePos]; }
	int32 GetFreeSize() { return BUFFER_SIZE - _writePos; }
	int32 GetDataSize() { return _writePos - _readPos; }
	CHAR* GetBufferPtrRead() { return &_buffer[_readPos]; }
	
	void Clear();
	void Next();
	void Move(int32 recvBytes);
	bool Read(int32 readBytes);
	bool IsReadable(int32 bytes) { return _writePos - _readPos >= bytes; }
	bool IsHeaderReadable() { return _writePos - _readPos >= sizeof(packet::PacketHeader); }

private:
	bool isFree(int32 bytes) { return BUFFER_SIZE - _writePos >= bytes; }

private:
	int32 _writePos;
	int32 _readPos;
	CHAR  _buffer[BUFFER_SIZE];
};

