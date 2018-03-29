#include "stdafx.h"
#include "MasterServer.h"
#include "ServerContainer.h"
#include "SServerDlg.h"

MasterServer::MasterServer()
{
}


MasterServer::~MasterServer()
{
}

void MasterServer::ServerAcceptRoutinue(SOCKET socket, SOCKADDR_IN sockaddr)
{
	ServerContainer* server_container = ServerContainer::GetInstance();

	Server* server = server_container->PopServer();

	if (server != NULL)
	{
		if (server->InitPeer(socket, sockaddr, IOCP::g_userID++) == true)
		{
			ServerContainer::GetInstance()->PushRogueServer(server);
			GameMessageManager::Instnace()->SendGameMessage(GM_ACCEPTUPEER, 0, 0, NULL);
		}
		else
		{
			server->ReleaseSocket();
			server_container->PushServer(server);
		}
	}
}

void MasterServer::ServerWorkRoutinue(SOCKET_CONTEXT* pCompletionKey, IO_OVERLAPPED* pOverlapped, int DwNumberBytes)
{
	Server* server = ServerContainer::GetInstance()->FindPeer(pCompletionKey->m_puser->GetId());

	if (pOverlapped->io_type == IO_RECV)
	{
		server->RecvPacket(DwNumberBytes);
	}
	else if (pOverlapped->io_type == IO_SENDING)
	{
		server->CheckSendPacket();
	}
	else // IO_NONE 혹은 에러
	{

	}
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
		//ServerContainer::GetInstance()->DisConnect((SOCKET_CONTEXT*)wParam);
		SOCKET_CONTEXT* context = (SOCKET_CONTEXT*)wParam;
		SPeer* peer = (SPeer*)wParam;
		Server* server = (Server*)wParam;
		char message[500];
		sprintf_s(message, "Disconnect Server : %s", Server::SERVERTYPEToString(server->GetType()));
		SServerDlg::GetInstance()->SetMessage(message);
	}break;
	case GM_PKTRECEIVE:
		break;
	case GM_TIMER:
		ServerContainer::GetInstance()->ServerCheckPing(wParam);
		break;
	default:
		break;
	}
}


