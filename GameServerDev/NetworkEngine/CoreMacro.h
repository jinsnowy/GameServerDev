#pragma once

#define INVALID_SESSION_VALUE -1
#define DEFAULT_BUF_SIZE 1024

#define check_sock_error(exp) ((exp) == SOCKET_ERROR)
#define was_io_pending() ((::WSAGetLastError() == WSA_IO_PENDING))
#define would_block(err) ((::WSAGetLastError() == WSAEWOULDBLOCK))
#define safe_close_event(h) if (h != NULL) { WSACloseEvent(h); h = NULL; }
#define safe_close_handle(h) if (h != NULL) { CloseHandle(h); h = NULL; }
#define get_last_err_msg() WSAGetLastErrorMsg().c_str()
#define get_last_err_msg_code(errCode) WSAGetLastErrorMsg(errCode).c_str()
#define size16(val)		static_cast<int16>(sizeof(val))
#define size32(val)		static_cast<int32>(sizeof(val))

#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}

#define ASSERT_CRASH(expr)			\
{									\
	if (!(expr))					\
	{								\
		CRASH("ASSERT_CRASH");		\
		__analysis_assume(expr);	\
	}								\
}
