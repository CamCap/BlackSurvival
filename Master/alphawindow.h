#pragma once

#include <windows.h>

#define WINDOWMODE_TRANSPARENT 0
#define WINDOWMODE_BLURBEHIND 1

#define WINDOWMODE_ERROR_LIBRARY_FAIL -1
#define WINDOWMODE_ERROR_CODE_FAIL -2
#define WINDOWMODE_ERROR_EXCUTE_FAIL -3

typedef BOOL( WINAPI*SetWindowCompositionAttribute )(HWND ,WINCOMPATTRDATA*);

enum ACCENT_STATE
{
	ACCENT_DISABLED = 0 ,
	ACCENT_ENABLE_GRADIENT = 1 ,
	ACCENT_ENABLE_TRANSPARENTGRADIENT = 2 ,
	ACCENT_ENABLE_BLURBEHIND = 3 ,
	ACCENT_INVALID_STATE = 4 ,
	_ACCENT_STATE_SIZE = 0xFFFFFFFF
};

typedef struct WINCOMPATTRDATA
{
	DWORD attribute; //�Ӽ� ������
	PVOID pData; //�Ӽ� ���� ������
	ULONG dataSize; //�Ӽ� ������
}WINCOMPATTRDATA;

typedef struct ACCENTPOLICY
{
	ACCENT_STATE nAccentState;
	DWORD nFlags;
	DWORD nColor;
	DWORD nAnimationId;
}ACCENTPOLICY;

int TransparentWindow( HWND hWnd ,int mode )
{
	const DWORD WCA_ACCENT_POLICY = 19;
	WINCOMPATTRDATA data = { 0, };
	ACCENTPOLICY pol;

	SetWindowCompositionAttribute SWCA;

	HMODULE hMod = LoadLibrary( TEXT( "user32.dll" ) );
	if( !hMod )
	{
		FreeLibrary( hMod );
		return WINDOWMODE_ERROR_LIBRARY_FAIL;
	}

	SWCA = (SetWindowCompositionAttribute)GetProcAddress( hMod ,"SetWindowCompositionAttribute" );
	if( !SWCA )
	{
		FreeLibrary( hMod );
		return WINDOWMODE_ERROR_CODE_FAIL;
	}

	memset( &pol ,NULL ,sizeof( pol ) );

	switch( mode )
	{
		//�޸��� �״�� ���ĺ���. �̰ɷ� �����ϸ� �������� ������ϱ� 
		//���⿡ ������ ��ü ����ϸ� ��¥ �̻ڰ� ����� �ִ�.
		case WINDOWMODE_TRANSPARENT: 
			pol.nAccentState = ACCENT_ENABLE_TRANSPARENTGRADIENT;
			pol.nFlags = 2;
			break;


		//�޸��� ��ó���Ǿ ����. �̰͵� ��¥ �̻۵�,
		//�� 8������ �׳� ������������ ����. ��10���� �����۵�.
		//�� 8������ dwm API �� ȣ���� ����Ѵ�.
		//�׷��� dwm �� ��10 ������ ���õ� ��
		case WINDOWMODE_BLURBEHIND:
			pol.nAccentState = ACCENT_ENABLE_BLURBEHIND;
			break;
	}

	data.attribute = WCA_ACCENT_POLICY; // (19)
	data.pData = &pol;
	data.dataSize = sizeof( pol );

	if( SWCA( hWnd ,&data ) )
	{
		FreeLibrary( hMod );
		return WINDOWMODE_ERROR_EXCUTE_FAIL;
	}
	FreeLibrary( hMod );
	return 0;
}