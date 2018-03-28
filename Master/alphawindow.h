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
	DWORD attribute; //속성 지정자
	PVOID pData; //속성 설정 데이터
	ULONG dataSize; //속성 사이즈
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
		//뒷면이 그대로 비쳐보임. 이걸로 지정하면 완전투명 윈도우니까 
		//여기에 반투명 객체 출력하면 진짜 이쁘게 만들수 있당.
		case WINDOWMODE_TRANSPARENT: 
			pol.nAccentState = ACCENT_ENABLE_TRANSPARENTGRADIENT;
			pol.nFlags = 2;
			break;


		//뒷면이 블러처리되어서 나옴. 이것도 진짜 이쁜데,
		//윈 8에서는 그냥 완전투명으로 나옴. 윈10에선 정상작동.
		//윈 8에서는 dwm API 를 호출해 써야한다.
		//그러나 dwm 은 윈10 에서는 무시됨 ㅠ
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