#include "stdafx.h"
#include "SServerDlg.h"
#include "ServerContainer.h"
#include "IOCP.h"
#include "resource.h"
#include "GameMessage.h"
#include "MasterServer.h"
#include <ctime>
#include <cstringt.h>
#include <atlstr.h>

SServerDlg* SServerDlg::m_instance = NULL;

SServerDlg::SServerDlg()
{
}

SServerDlg::~SServerDlg()
{
	KillTimer(m_hWnd, TIMER_ID);//종류//종류
}

SServerDlg* SServerDlg::GetInstance()
{
	if (m_instance == NULL)
		m_instance = new SServerDlg();

	return m_instance;
}

void SServerDlg::OnInitServer(HWND hWnd)
{
	m_hWnd = hWnd;

	m_hWndMsg = GetDlgItem(m_hWnd, IDC_LOG);

	m_hTimer = GetDlgItem(m_hWnd, IDC_TIMEEDIT);
	m_Day = 0;
	m_Hour = 0;
	m_Minute = 0;
	m_TimeCount = 0;

	m_iocp = IOCP::GetInstance();
	m_iocp->CreateIOCP(&MasterServer::ServerAcceptRoutinue, &MasterServer::ServerWorkRoutinue); //이거 accept랑 workthread 좀 수정하자

	m_server = ServerContainer::GetInstance();
	HANDLE handle = CreateThread(NULL, 0, GameMessageManager::GameMsgLoop, NULL, 0, NULL);

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

void SServerDlg::StartServer(HINSTANCE hInstance, int resID, HWND parentHwnd)
{
	DialogBox(hInstance, MAKEINTRESOURCE(resID), parentHwnd, (DLGPROC)ServerProc);
}

void SServerDlg::SetMessage(const char *s)
{
	SendMessage(m_hWndMsg, LB_ADDSTRING, (WPARAM)0, (LPARAM)s);
}

void SServerDlg::SetRunTime()
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
		SServerDlg::GetInstance()->OnInitServer(hWnd);
		break;
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
		SServerDlg::GetInstance()->SetRunTime();
		//GameMessageManager::Instnace()->SendGameMessage(GM_TIMER, GetTickCount(), 0, NULL);
		break;
	default:
		break;
	}

	return FALSE;
}