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
	KillTimer(m_hWnd, TIMER_ID);//종류//종류
	SAFE_DELETE(m_message);
	SAFE_DELETE(m_db);


	SAFE_DELETE(m_iocp);
	SAFE_DELETE(m_container);
}


void LoginDlg::OnInitServer(HWND hWnd)
{
	m_hWnd = hWnd;

	m_hWndMsg = GetDlgItem(m_hWnd, IDC_LOG);

	m_hTimer = GetDlgItem(m_hWnd, IDC_TIMEEDIT);
	m_Day = 0;
	m_Hour = 0;
	m_Minute = 0;
	m_TimeCount = 0;

	m_iocp = new LoginIOCP;
	m_iocp->SetRoutinue(LoginServerRoutinue::LoginAccept, LoginServerRoutinue::LoginWork, LoginServerRoutinue::LoginDisconnect);
	m_iocp->CreateIOCP();

	m_container = new UserContainer;//MasterServerContainer::GetInstance();

	m_message = new GameMessageManager;//GameMessageManager::GetInstance();
	HANDLE handle = CreateThread(NULL, 0, GameMessageManager::GameMsgLoop, NULL, 0, NULL);
	
	m_db = new DBManager;

	//////////////////////////////////////////
	CString str;
	str.Format(_T("=================초기화 종료================="));
	SetMessage(LPSTR(LPCTSTR(str)));

	ShowWindow(hWnd, SW_SHOWNORMAL);
	SetTimer(m_hWnd, TIMER_ID, 10000, NULL);

	SYSTEMTIME st;
	GetLocalTime(&st);

	char year[5];
	wsprintfA(year, "%d", st.wYear);
	char month[3];
	if (st.wMonth < 10)
		wsprintfA(month, "0%d", st.wMonth);
	else
		wsprintfA(month, "%d", st.wMonth);
	char day[3];
	if (st.wDay < 10)
		wsprintfA(day, "0%d", st.wDay);
	else
		wsprintfA(day, "%d", st.wDay);

	sprintf_s(m_RunTime, "%d일%2d시%2d분", m_Day, m_Hour, m_Minute);
	SetWindowTextA(m_hTimer, m_RunTime);

	m_RealDay = st.wDay;
	m_RealHour = st.wHour;
	m_RealMinute = st.wMinute;
	m_WriteTime = m_RealMinute % 10;

	str.Format(_T("%d일%2d시%2d분 서버 가동 시작"), st.wDay, st.wHour, st.wMinute);
	SetMessage(LPSTR(LPCTSTR(str)));
}

void LoginDlg::StartServer(HINSTANCE hInstance, int resID, HWND parentHwnd)
{
	DialogBox(hInstance, MAKEINTRESOURCE(resID), parentHwnd, (DLGPROC)ServerProc);
}

void LoginDlg::SetMessage(const char *s)
{
	SendMessage(m_hWndMsg, LB_ADDSTRING, (WPARAM)0, (LPARAM)s);
}

void LoginDlg::SetRunTime()
{
	m_TimeCount++;
	if (m_TimeCount == 6)
	{
		//가동 시간
		m_Minute++;
		if (m_Minute >= 60)
		{
			m_Hour++;
			m_Minute = 0;
			if (m_Hour >= 24)
			{
				m_Day++;
				m_Hour = 0;
			}
		}
		//wsprintfA(m_RunTime, "%d일%2d시%2d분", m_Day, m_Hour, m_Minute);
		CString str;
		str.Format(_T("%d일%2d시%2d분"), m_Day, m_Hour, m_Minute);
		SetWindowText(m_hTimer, LPCWSTR(LPCTSTR(str)));

		m_TimeCount = 0;
	}
}

INT_PTR CALLBACK ServerProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		LoginDlg::GetInstance()->OnInitServer(hWnd);
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
		LoginDlg::GetInstance()->SetRunTime();
		//GameMessageManager::GetInstance()->SendGameMessage(GM_TIMER, GetTickCount(), 0, NULL);
		break;
	default:
		break;
	}

	return FALSE;
}