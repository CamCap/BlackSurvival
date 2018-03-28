#pragma once
#include "CriticalSection.h"

class IOCP;
class GameMessageManager;
class ServerContainer;

//----------------------- timer id ----------------------//
#define TIMER_ID                100

class SServerDlg
{
public:
	static SServerDlg* GetInstance();

protected:
	HWND m_hWnd;
	HWND m_hWndMsg;				// �޼����� ����� ����Ʈ �ڽ� �ڵ�.
	HWND m_hTimer;				//���� ���� �ð� ����Ʈ�ڽ� �ڵ�

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
	ServerContainer* m_server;

public:
	void SetMessage(const char *s);

	SServerDlg();
	~SServerDlg();

	void OnInitServer(HWND hWnd);
	void StartServer(HINSTANCE hInstance, int resID, HWND parentHwnd);

	BOOL OnExit(HWND hWnd);

	HWND GetHWND() { return m_hWnd; }

	void SetRunTime();
//	void SetMessage()
private:
	static SServerDlg* m_instance;
};

INT_PTR CALLBACK ServerProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);




