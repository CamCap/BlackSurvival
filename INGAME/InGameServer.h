#pragma once
#include "GameMessage.h"
#include "InGameIOCP.h"
#include "InGameUserContainer.h"

class InGameServerRoutinue
{
public:
	static void InGameAccept(SOCKET socket, SOCKADDR_IN addr)
	{
		InGameUserContainer* user_container = InGameUserContainer::GetInstance();

		InGameUser* user = user_container->PopWaitUser();

		if (user != NULL)
		{
			if (InGameIOCP::GetInstance()->RegisterCompletionPort(socket, reinterpret_cast<SPeer*>(user)) == true)
			{
				user_container->AuthUser(user);
				user->InitPeer(socket, addr, SIOCP::g_userID++);
				GameMessageManager::GetInstance()->SendGameMessage(GM_ACCEPTUPEER, 0, 0, NULL);
			}
			else
			{
				user_container->DisConnectUser(user);
			}
		}
	}

	static void InGameWork(SPeer* peer, IO_OVERLAPPED* overlapped, int recv_byte)
	{
		InGameUser* puser = InGameUserContainer::GetInstance()->Find(peer->GetId());

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

	static void InGameDissconet(SPeer* peer)
	{
		InGameUser* puser = InGameUserContainer::GetInstance()->Find(peer->GetId());
		InGameUserContainer::GetInstance()->DisConnectUser(puser);
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
		break;
	case GM_PKTRECEIVE:
		break;
	case GM_TIMER:
		InGameUserContainer::GetInstance()->ServerPingCheck(wParam);
		break;
	default:
		break;
	}
}


