#include "stdafx.h"
#include "InGameDlg.h"
#include "InGameServer.h"
#include "InGameIOCP.h"
#include "InGameUserContainer.h"

template<> InGameDlg* SSingleton<InGameDlg>::ms_singleton = 0;

InGameDlg::InGameDlg()
{
}


InGameDlg::~InGameDlg()
{
	SAFE_DELETE(m_message);

	SAFE_DELETE(m_iocp);
	SAFE_DELETE(m_container);
}

void InGameDlg::StartDlg(HINSTANCE hInstance, int resID, HWND parentHwnd)
{
//	SDlg::DlgOption opt(parentHwnd, hInstance, resID, ServerProc);

//	DialogBox(hInstance, MAKEINTRESOURCE(resID), parentHwnd, ServerProc);

	__super::StartDlg({ parentHwnd, hInstance, (DWORD)resID, ServerProc });
}

void InGameDlg::OnInitDlg(HWND hWnd)
{
	__super::OnInitDlg(hWnd);
	__super::SetTimer(IDC_LOG_LIST, 1000);

	m_message = new GameMessageManager;//GameMessageManager::GetInstance();
	HANDLE handle = CreateThread(NULL, 0, GameMessageManager::GameMsgLoop, NULL, 0, NULL);

	m_iocp = new InGameIOCP;
	m_iocp->m_RoutinueAccept = InGameServerRoutinue::InGameAccept;
	m_iocp->m_RoutinueWork = InGameServerRoutinue::InGameWork;
	m_iocp->m_RoutinueDisconnect = InGameServerRoutinue::InGameDissconet;
	m_iocp->CreateIOCP();

	m_container = new InGameUserContainer;
}

//INT_PTR InGameDlg::BTZ_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//	return m_dlg.BTZ_PROC(hWnd, uMsg, wParam, lParam);
//}

INT_PTR CALLBACK ServerProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		//m_dlg.SetTimer(IDC_TIME_EDIT, 1000);
		InGameDlg::GetInstance()->OnInitDlg(hWnd);
		break;
	case WM_CLOSE:
	case WM_QUIT:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDCANCEL:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_TIMER:
		GameMessageManager::GetInstance()->SendGameMessage(GM_TIMER, GetTickCount(), 0, NULL);

		break;
	default:
		break;
	}

	return InGameDlg::GetInstance()->BTZ_PROC(hWnd, uMsg, wParam, lParam);
	///return InGameDlg::GetInstance()->BTZ_Proc(hWnd, uMsg, wParam, lParam);
}