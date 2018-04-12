#pragma once
#include "Log.h"
#include "iocp.h"
#include "GameMessage.h"


class MasterServer
{
public:
	static void ServerAcceptRoutinue(SOCKET socket, SOCKADDR_IN sockaddr);
	static void ServerWorkRoutinue(SPeer* pCompletionKey, IO_OVERLAPPED* pOverlapped, int DwNumberBytes);
	static void ServerDisConnectRoutinue(SPeer* pCompletionKey);
public:
	MasterServer();
	~MasterServer();
};

