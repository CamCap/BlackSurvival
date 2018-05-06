#pragma once
#include "SDlg.h"
#include "SSingleton.h"

class InGameDlg
	:public SSingleton<InGameDlg>, public SDlg
{
public:
	InGameDlg();
	~InGameDlg();

	void StartDlg(HINSTANCE hInstance, int resID, HWND parentHwnd);
	void OnInitDlg(HWND hWnd); 
	void SetRunTime() { __super::SetRunTime(); }
//	INT_PTR BTZ_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	class InGameIOCP* m_iocp;
	class GameMessageManager* m_message;
	class InGameUserContainer* m_container;
};



INT_PTR CALLBACK ServerProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
