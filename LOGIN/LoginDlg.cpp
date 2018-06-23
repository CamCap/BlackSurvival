#include "stdafx.h"
#include "LoginDlg.h"
#include "resource.h"
#include <ctime>
#include <cstringt.h>
#include <atlstr.h>
#include "LoginIOCP.h"
#include "UserContainer.h"
#include "GameMessage.h"
#include "LoginServer.h"
#include "DBManager.h"

template<> LoginDlg* SSingleton<LoginDlg>::ms_singleton = 0;

LoginDlg::LoginDlg()
{
}

LoginDlg::~LoginDlg()
{
//	KillTimer(m_hWnd, TIMER_ID);//종류//종류
	SAFE_DELETE(m_message);
	SAFE_DELETE(m_db);


	SAFE_DELETE(m_iocp);
	SAFE_DELETE(m_container);
}


void LoginDlg::OnInitDlg(HWND hWnd)
{
	__super::OnInitDlg(hWnd);
	__super::SetTimer(GetDlgItem(hWnd, IDC_LOG_LIST), GetDlgItem(hWnd, IDC_TIME_EDIT), 1000);


	m_iocp = new LoginIOCP;
	m_iocp->SetRoutinue(LoginServerRoutinue::LoginAccept, LoginServerRoutinue::LoginWork, LoginServerRoutinue::LoginDisconnect);
	m_iocp->CreateIOCP();

	SIOCP* iocp = new SIOCP;

	iocp->m_RoutinueAccept = [&](SOCKET socket, SOCKADDR_IN addr) {		
		UserContainer* user_container = UserContainer::GetInstance();

		User* user = user_container->PopWaitUser();

		if (user != NULL)
		{
			if (LoginIOCP::GetInstance()->RegisterCompletionPort(socket, reinterpret_cast<SPeer*>(user)) == true)
			{
				user_container->PushActiveUser(user);
				user->InitPeer(socket, addr, SIOCP::g_userID++);
				GameMessageManager::GetInstance()->SendGameMessage(GM_ACCEPTUPEER, 0, 0, NULL);
			}
			else
			{
				user_container->DisConnectUser(user);
			}
		}
	};
	iocp->m_RoutinueWork = [&](SPeer* peer, IO_OVERLAPPED* overlapped, int recv_byte) {
		User* puser = UserContainer::GetInstance()->Find(peer->GetID());

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
	};

	m_container = new UserContainer;//MasterServerContainer::GetInstance();

	m_message = new GameMessageManager;//GameMessageManager::GetInstance();
	HANDLE handle = CreateThread(NULL, 0, GameMessageManager::GameMsgLoop, NULL, 0, NULL);

	m_db = new DBManager;
}

void LoginDlg::StartDlg(HINSTANCE hInstance, int resID, HWND parentHwnd)
{
	__super::StartDlg({ parentHwnd, hInstance, (DWORD)resID, ServerProc, false });
}

INT_PTR CALLBACK ServerProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		LoginDlg::GetInstance()->OnInitDlg(hWnd);
		break;
	case WM_CLOSE:
	case WM_QUIT:
		GameMessageManager::GetInstance()->SendGameMessage(GM_QUIT, 0, 0, NULL);
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDCANCEL:
			GameMessageManager::GetInstance()->SendGameMessage(GM_QUIT, 0, 0, NULL);
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_TIMER:
//		LoginDlg::GetInstance()->SetRunTime();
		GameMessageManager::GetInstance()->SendGameMessage(GM_TIMER, GetTickCount(), 0, NULL);
		break;
	default:
		break;
	}

	return LoginDlg::GetInstance()->BTZ_PROC(hWnd, uMsg, wParam, lParam);
}