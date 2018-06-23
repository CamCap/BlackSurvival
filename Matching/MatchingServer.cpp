#include "stdafx.h"
#include "MatchingServer.h"
#include "UserMatchingManager.h"
#include "MatchingDlg.h"

MatchingServer::MatchingServer()
{
}

MatchingServer::~MatchingServer()
{
}

void MatchingServer::MatchingAccept(SOCKET socket, SOCKADDR_IN addr)
{
	UserMatchingManager* user_container = UserMatchingManager::GetInstance();

	MatchUser* user = user_container->PopWaitUser();

	if (user != NULL)
	{
		if (MatchingDlg::GetInstance()->RegisterCompletionPort(socket, reinterpret_cast<SPeer*>(user)) == true)
		{
			user_container->PushActiveUser(user);
			user->InitPeer(socket, addr, SIOCP::g_userID++);
			GameMessageManager::GetInstance()->SendGameMessage(GM_ACCEPTUPEER, 0, 0, NULL);
		//	UserMatchingManager::GetInstance()->SetMatching()
		}
		else
		{
			user_container->DisConnectUser(user);
		}
	}
}

void MatchingServer::MatchingWork(SPeer * peer, IO_OVERLAPPED * overlapped, int recv_byte)
{
	MatchUser* puser = UserMatchingManager::GetInstance()->Find(peer->GetId());

	if (puser == NULL) return;

	if (overlapped->io_type == IO_RECV)
	{
		peer->RecvPacket(recv_byte);
	}
	else if (overlapped->io_type == IO_SENDING)
	{
		peer->CheckSendPacket();
	}
	else // IO_NONE 혹은 에러
	{
	}
}

void MatchingServer::MatchingDissconet(SPeer * peer)
{
	MatchUser* puser = UserMatchingManager::GetInstance()->Find(peer->GetId());
	UserMatchingManager::GetInstance()->DisConnectUser(puser);
}

void GameMessageProcedure(DWORD msg, DWORD wParam, DWORD lParam, const char * pPacket)
{
	switch (msg)
	{
	case GM_ACCEPTUPEER:
		break;
	case GM_ERROR:
		break;
	case GM_DISCONNECTUSER:
	{
	}break;
	case GM_PKTRECEIVE:
		break;
	case GM_TIMER:
		UserMatchingManager::GetInstance()->ServerPingCheck(wParam);
		break;
	default:
		break;
	}
}