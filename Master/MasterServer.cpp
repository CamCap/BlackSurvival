#include "stdafx.h"
#include "MasterServer.h"
#include "ServerDlg.h"
#include "MasterServerContainer.h"
#include "Server.h"

MasterServer::MasterServer()
{
}


MasterServer::~MasterServer()
{
}

void MasterServer::ServerAcceptRoutinue(SOCKET socket, SOCKADDR_IN sockaddr)
{
	MasterServerContainer* server_container = MasterServerContainer::GetInstance();
	
	Server* server = server_container->PopWaitServer();

	if (server != NULL)
	{
		if (IOCP::GetInstance()->RegisterCompletionPort(socket, dynamic_cast<SPeer*>(server)) == true)
		{
			server_container->AuthServer(server);
			server->InitPeer(socket, sockaddr, SIOCP::g_userID++);
			GameMessageManager::GetInstance()->SendGameMessage(GM_ACCEPTUPEER, 0, 0, NULL);
		}
		else
		{
			server_container->PushWaitServer(server);
		}
	}	
}

void MasterServer::ServerWorkRoutinue(SPeer* pCompletionKey, IO_OVERLAPPED* pOverlapped, int DwNumberBytes)
{
	Server* server = MasterServerContainer::GetInstance()->Find(pCompletionKey->GetId());

	if (server == NULL) return;

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

void MasterServer::ServerDisConnectRoutinue(SPeer * pCompletionKey)
{
	Server* pServer = MasterServerContainer::GetInstance()->Find(pCompletionKey->GetId());
	MasterServerContainer::GetInstance()->DisConnectServer(pServer);
//	pCompletionKey->ReleaseSocket();
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
		SPeer* peer = (SPeer*)wParam;
		Server* server = MasterServerContainer::GetInstance()->Find(peer->GetId());
		if (server == NULL) break;
		char message[500];
		sprintf_s(message, "Disconnect Server : %s", Server::SERVERTYPEToString(server->GetType()));
		ServerDlg::GetInstance()->SetMessage(message);
	}break;
	case GM_PKTRECEIVE:
		break;
	case GM_TIMER:
		MasterServerContainer::GetInstance()->ServerPingCheck(wParam);
		break;
	default:
		break;
	}
}


