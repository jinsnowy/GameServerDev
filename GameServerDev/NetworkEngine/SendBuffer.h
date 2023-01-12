#pragma once

struct WriteData
{
	std::vector<WSABUF> buffers;
	std::vector<BufferSegment> segments;

	void Append(const BufferSegment& segment) { segments.push_back(segment); buffers.push_back(segment.AsBufffer()); }

	bool IsEmpty() { return segments.empty(); }

	void Clear() { buffers.clear(); segments.clear(); }
};

class SendBuffer
{
private:
	StdMutex				_sync;
	WriteData				_writeData;

public:
	SendBuffer();

	~SendBuffer();

	void Pend(const BufferSegment& segment);

	WriteData Flush();

	void Clear();
};