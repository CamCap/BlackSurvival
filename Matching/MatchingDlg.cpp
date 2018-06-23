#include "stdafx.h"
#include "MatchingDlg.h"
#include "GameMessage.h"


MatchingDlg::MatchingDlg()
{
}


MatchingDlg::~MatchingDlg()
{
}

void MatchingDlg::OnInitDlg(HWND hWnd)
{
	__super::OnInitDlg(hWnd);
	__super::SetTimer(GetDlgItem(hWnd, IDC_LOG_LIST), GetDlgItem(hWnd, IDC_TIME_EDIT), 1000);
}


void MatchingDlg::StartDlg(HINSTANCE hInstance, int resID, HWND parentHwnd)
{
	__super::StartDlg({ parentHwnd, hInstance, (DWORD)resID, ServerProc, false });
}

INT_PTR CALLBACK ServerProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		MatchingDlg::GetInstance()->OnInitDlg(hWnd);
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

	return MatchingDlg::GetInstance()->BTZ_PROC(hWnd, uMsg, wParam, lParam);
}