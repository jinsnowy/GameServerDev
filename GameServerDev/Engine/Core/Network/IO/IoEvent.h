#pragma once

namespace Core {
	namespace Network {
		namespace IO {
			enum class IoType
			{
				IO_READ,
				IO_WRITE,
				IO_CONNECT,
				IO_DISCONNECT,
				IO_ACCEPT,
			};

			const char* GetIoTypeStr(IoType type);

			struct IoEvent : WSAOVERLAPPED
			{
				IoType ioType;

				std::function<void(int32, DWORD)> task;

				template<typename T>
				IoEvent(IoType _ioType, T&& callback)
					:
					WSAOVERLAPPED{}, ioType(_ioType), task(std::forward<T>(callback))
				{
				}

				void operator()(int32 errorID, DWORD bytesTransferred) { task(errorID, bytesTransferred); }

				void release() { System::Memory::pool_delete(this); }
			};

			template<typename T>
			IoEvent* MakeWriteTask(T&& callback) { return POOL_NEW<IoEvent>(IoType::IO_WRITE, std::forward<T>(callback)); }

			template<typename T>
			IoEvent* MakeReadTask(T&& callback) { return POOL_NEW<IoEvent>(IoType::IO_READ, std::forward<T>(callback)); }

			template<typename T>
			IoEvent* MakeConnectTask(T&& callback) { return POOL_NEW<IoEvent>(IoType::IO_CONNECT, std::forward<T>(callback)); }

			template<typename T>
			IoEvent* MakeDisconnectTask(T&& callback) { return POOL_NEW<IoEvent>(IoType::IO_DISCONNECT, std::forward<T>(callback)); }

			template<typename T>
			IoEvent* MakeAcceptTask(T&& callback) { return POOL_NEW<IoEvent>(IoType::IO_ACCEPT, std::forward<T>(callback)); }
		}
	}
}