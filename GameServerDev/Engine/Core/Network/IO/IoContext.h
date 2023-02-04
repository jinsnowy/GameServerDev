#pragma once

class IoObject;
class IoContext
{
private:
	atomic<bool> _disposed;
	HANDLE _iocpHandle;

public:
	IoContext();
	~IoContext();

	void RegisterHandle(HANDLE handle);

	void Dispatch(DWORD timeOutMs = INFINITE);

	void Dispose();

	bool isFinished() { return _disposed; }
};
