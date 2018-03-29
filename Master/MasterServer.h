#pragma once
#include "Log.h"
#include "iocp.h"
#include "GameMessage.h"


class MasterServer
{
public:
	static void ServerAcceptRoutinue(SOCKET socket, SOCKADDR_IN sockaddr);
	static void ServerWorkRoutinue(SOCKET_CONTEXT* pCompletionKey, IO_OVERLAPPED* pOverlapped, int DwNumberBytes);
public:
	MasterServer();
	~MasterServer();
};

