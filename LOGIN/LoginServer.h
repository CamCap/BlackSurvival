#pragma once

#include "UserContainer.h"
#include "LoginIOCP.h"
#include "GameMessage.h"

class LoginServerRoutinue
{
public:
	static void LoginAccept(SOCKET socket, SOCKADDR_IN addr)
	{
		UserContainer* user_container = UserContainer::GetInstance();

		User* user = user_container->PopWaitServer();

		if (user != NULL)
		{
			if (LoginIOCP::GetInstance()->RegisterCompletionPort(socket, reinterpret_cast<SPeer*>(user)) == true)
			{
				user_container->AuthServer(user);
				user->InitPeer(socket, addr, SIOCP::g_userID++);
				GameMessageManager::GetInstance()->SendGameMessage(GM_ACCEPTUPEER, 0, 0, NULL);
			}
			else
			{
				user_container->DisConnectServer(user);
			}
		}
	}
	static void LoginWork(SPeer* peer, IO_OVERLAPPED* overlapped, int recv_byte)
	{
		User* puser = UserContainer::GetInstance()->Find(peer->GetId());

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

	static void LoginDisconnect(SPeer* peer)
	{
		User* puser = UserContainer::GetInstance()->Find(peer->GetId());
		UserContainer::GetInstance()->DisConnectServer(puser);
	}
};


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
		UserContainer::GetInstance()->ServerPingCheck(wParam);
		break;
	default:
		break;
	}
}


