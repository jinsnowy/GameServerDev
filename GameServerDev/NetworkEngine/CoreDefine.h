#pragma once

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;
typedef uint64 SessionID;

using CondVar = std::condition_variable;
using Thread = std::thread;
using Mutex = std::mutex;
using UniqueLock = std::unique_lock<std::mutex>;
using LockGuard = std::lock_guard<std::mutex>;

using AlarmPtr = std::shared_ptr<class Alarm>;
using BufferSourcePtr = shared_ptr<class BufferSource>;
using SessionPtr = std::shared_ptr<class Session>;
using SessionWeakPtr = std::weak_ptr<class Session>;
using SessionPtrCRef = const SessionPtr&;
using NetworkPtr = std::shared_ptr<class TcpNetwork>;
using NetworkPtrCRef = const std::shared_ptr<class TcpNetwork>&;
using ListenerPtr = std::shared_ptr<class TcpListener>;
using SessionFactory = std::function<SessionPtr()>;
using NetworkFactory = std::function<NetworkPtr(class ServiceBase&)>;
using OnAcceptFunc = std::function<bool(NetworkPtr)>;
using PacketHandlerFunc = std::function<void(SessionPtr)>;
using HandshakePtr = std::unique_ptr<class Handshake>;
using TaskPtr = std::unique_ptr<class Task>;
using PlayerPtr = std::shared_ptr<class Player>;
using ClientSessionFactory = std::function<std::shared_ptr<class ClientSession>()>;
using ServerSessionFactory = std::function<std::shared_ptr<class ServerSession>()>;

static const char* get_bool_str(const bool& v) { return v ? "true" : "false"; }
