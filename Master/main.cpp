#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include "SServerDlg.h"
#include "resource.h"

#if defined(_WIN64)
#pragma comment(lib, "Sin_Library_64.lib")
#elif defined(_WIN32)
#pragma comment(lib, "Sin_Library_32.lib")
#endif



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SServerDlg* dlg = new SServerDlg();
	dlg->StartServer(hInstance, IDD_MASTER_DIALOG, NULL);

	delete dlg;
}