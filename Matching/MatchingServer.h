#pragma once
#include "SIocp.h"
#include "GameMessage.h"
#include "SSingleton.h"

class MatchingServer
	:public SIOCP, public SSingleton<MatchingServer>
{
public:
	MatchingServer();
	~MatchingServer();

	void MatchingAccept(SOCKET socket, SOCKADDR_IN addr);
	void MatchingWork(SPeer* peer, IO_OVERLAPPED* overlapped, int recv_byte);
	void MatchingDissconet(SPeer* peer);

private:

};


void GameMessageProcedure(DWORD msg, DWORD wParam, DWORD lParam, const char * pPacket);