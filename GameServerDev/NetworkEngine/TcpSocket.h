#pragma once

class ServiceBase;
class TcpSocket
{
	friend class ServiceBase;
	friend class TcpListenerSocket;
protected:
	SOCKET	   _socket;

private:
	ServiceBase& _service;
	atomic<bool> _disposed;

public:
	TcpSocket(ServiceBase& service);
	virtual ~TcpSocket();

	SOCKET   GetSocket() { return _socket; }

	bool SetLinger(uint16 onoff, uint16 linger);
	bool SetReuseAddress(bool flag);
	bool SetRecvBufferSize(int32 size);
	bool SetSendBufferSize(int32 size);
	bool SetTcpNoDelay(bool flag);

	bool IsOk();
	void Dispose();
	bool IsDisposed();
	void Close();
};