#pragma once
#include "SDlg.h"
#include "SSingleton.h"
#include "SIocp.h"

class MatchingDlg
	:public SDlg, public SSingleton<MatchingDlg>, public SIOCP
{
public:
	MatchingDlg();
	~MatchingDlg();

public:
	void OnInitDlg(HWND hWnd);
	void StartDlg(HINSTANCE hInstance, int resID, HWND parentHwnd);
};


INT_PTR CALLBACK ServerProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);