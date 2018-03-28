#include "stdafx.h"
#include "MasterServer.h"
#include "ServerManager.h"
#include "SServerDlg.h"

MasterServer::MasterServer()
{
}


MasterServer::~MasterServer()
{
}

void MasterServer::ServerAcceptRoutinue(SOCKET socket, SOCKADDR_IN sockaddr)
{

	SOCKET_CONTEXT socket_context;
	ServerContainer* server_container = ServerContainer::GetInstance();

	Server* server = server_container->PopServer();

	if (server != NULL)
	{
		socket_context.m_puser = server;
		socket_context.m_socket = socket;
		socket_context.m_addr = sockaddr;

		if (IOCP::GetInstance()->RegisterCompletionPort(&socket_context) == false)
		{

		}
		else
		{
			server->InitPeer(socket, sockaddr, IOCP::g_userID++);

			ServerContainer::GetInstance()->PushServer(server);
			비인증된 서버를 인증한 후에 컨테이너에 넣어야될 것같은데...
			GameMessageManager::Instnace()->SendGameMessage(GM_ACCEPTUPEER, 0, 0, NULL);
		}
	}
}

void MasterServer::ServerWorkRoutinue()
{
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
		IOCP::GetInstance()->PostCompletionStatus(wParam, 0, (OVERLAPPED*)lParam);
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


