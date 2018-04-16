// LOGIN.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "LOGIN.h"
#include "LoginDlg.h"
#include "MySqlManager.h"

#if defined(_WIN64)
#pragma comment(lib, "Sin_Library_64.lib")
#elif defined(_WIN32)
#pragma comment(lib, "Sin_Library_32.lib")
#endif



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LoginDlg* dlg = new LoginDlg;
	dlg->StartServer(hInstance, IDD_LOGIN_DLG, NULL);
	delete dlg;
}