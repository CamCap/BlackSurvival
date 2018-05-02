#include "stdafx.h"
#include <Windows.h>
#include "ServerDlg.h"
#include "resource.h"

#if defined(_WIN64)
#pragma comment(lib, "Sin_Library_64.lib")
#elif defined(_WIN32)
#pragma comment(lib, "Sin_Library_32.lib")
#endif



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ServerDlg* dlg = new ServerDlg();
	
	dlg->StartServer(hInstance, IDD_MASTER_DIALOG, NULL);

	delete dlg;
}