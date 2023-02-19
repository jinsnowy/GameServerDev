#pragma once
namespace Core {
	namespace Network {
		namespace IO {
			class IoContext : public IThreadStaticSingleton<IoContext>
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
		}
	}
}