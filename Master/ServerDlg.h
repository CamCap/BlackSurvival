#pragma once
#include "CriticalSection.h"
#include "SSingleton.h"
class IOCP;
class GameMessageManager;
class MasterServerContainer;

//----------------------- timer id ----------------------//
#define TIMER_ID                100

class ServerDlg
	:public SSingleton<ServerDlg>
{
protected:
	HWND m_hWnd;
	HWND m_hWndMsg;				// 메세지를 출력할 리스트 박스 핸들.
	HWND m_hTimer;				//서버 가동 시간 에디트박스 핸들

	DWORD m_Day;
	DWORD m_Hour;
	DWORD m_Minute;
	DWORD m_RealDay;
	DWORD m_RealHour;
	DWORD m_RealMinute;
	DWORD m_WriteTime;
	DWORD m_TimeCount;
	char m_RunTime[15];

	SCriticalSection m_cs;

	IOCP * m_iocp;
	GameMessageManager* m_message;
	MasterServerContainer* m_server;

public:
	ServerDlg();
	~ServerDlg();
	void SetMessage(const char *s);


	void OnInitServer(HWND& hWnd);
	void StartServer(HINSTANCE hInstance, int resID, HWND parentHwnd);

	BOOL OnExit(HWND hWnd);

	HWND GetHWND() { return m_hWnd; }


	void SetRunTime();
//	void SetMessage()
};

INT_PTR CALLBACK ServerProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);




