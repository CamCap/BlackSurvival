#pragma once
#include "SSingleton.h"
#include "SDlg.h"


#define TIMER_ID                100

class LoginIOCP;
class UserContainer;
class GameMessageManager;
class DBManager;

class LoginDlg
	:public SSingleton<LoginDlg>, public SDlg
{
protected:
	class LoginIOCP* m_iocp;
	class UserContainer* m_container;
	class GameMessageManager* m_message;
	class DBManager* m_db;

public:
	LoginDlg();
	~LoginDlg();

	void OnInitDlg(HWND hWnd);
	void StartDlg(HINSTANCE hInstance, int resID, HWND parentHwnd);

	void SetMatchNum(int num) { m_matchnum = num;}
	int GetMatchNum() { return m_matchnum; }
private:
	int m_matchnum;
};

INT_PTR CALLBACK ServerProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



