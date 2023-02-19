#pragma once

class DBConnection;
namespace Core {
	namespace Network {
		namespace IO {
			class IoContext;
		}
	}
	namespace System {
		class ExecutionContext;
		class ThreadContext : public IThreadStaticSingleton<ThreadContext>
		{
			friend class ServiceBase;
		private:
			Network::IO::IoContext* _io_context;
			ExecutionContext* _exec_context;
			DBConnection* _db_conn;
			atomic<bool> _disposed;

		public:
			ThreadContext();
			~ThreadContext();

			ExecutionContext* GetExecutionContext() { return _exec_context; }
			Network::IO::IoContext* GetIoContext() { return _io_context; }
			DBConnection* GetDBConn() { return _db_conn; }

			void Process();
			void Destroy();
		};
	}
}