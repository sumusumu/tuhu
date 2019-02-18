//헤더파일을 사용한다
#include "stdafx.h"
#include "mainGame.h"

//==============================================
// - 2015. 06. 30 - ## 전역변수는 여기다 선언한다 ##
//==============================================
HINSTANCE _hInstance;
HWND _hWnd;

//마우스 좌표
POINT _ptMouse;

mainGame _mg;

BOOL _leftButtonDown = FALSE;
BOOL _rightButtonDown = FALSE;

//==============================================
// - 2015. 06. 30 - ## 함수 프로토 타입 선언 ##
//==============================================

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowsSize(int x, int y, int width, int height);


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;		//운영체제에서 발생하는 메시지 정보를 저장하기 위한 구조체(선언)
	WNDCLASS wndClass;	//윈도우의 정보를 저장하기 위한 구조체 선언

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;										//클래스 여분 메모리
	wndClass.cbWndExtra = 0;										//윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//윈도우 백그라운드 색상
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//윈도우 커서
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//윈도우 아이콘
	wndClass.hInstance = hInstance;									//윈도우 인스턴스
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//프로시져
	wndClass.lpszClassName = WINNAME;								//클래스 이름
	wndClass.lpszMenuName = NULL;									//메뉴이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//윈도우 스따일~

	//윈도우 클래스 등록
	RegisterClass(&wndClass);


#ifdef FULLSCREEN
	DEVMODE dm;

	ZeroMemory(&dm, sizeof(DEVMODE));

	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = 32;
	dm.dmPelsWidth = 1024;
	dm.dmPelsHeight = 768;
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	//원래 해상도로 되돌리자
	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}

	//윈도우 생성
	_hWnd = CreateWindow(
		WINNAME,						//윈도우 클래스 이름
		WINNAME,						//윈도우 타이틀바에 나타낼 문자열
		WS_POPUPWINDOW | WS_MAXIMIZE,	//윈도우 스타일
		WINSTARTX,						//윈도우 창 시작 X좌표
		WINSTARTY,						//윈도우 창 시작 Y좌표
		GetSystemMetrics(SM_CXSCREEN),	//윈도우 가로크기
		GetSystemMetrics(SM_CYSCREEN),	//윈도우 세로크기
		NULL,							//부모 윈도우 유무
		(HMENU)NULL,					//메뉴핸들
		hInstance,						//인스턴스 윈도우 지정
		NULL);

	//클라이언트 영역이 재설정 되었음.
	setWindowsSize(WINSTARTX, WINSTARTY, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
#else
	//윈도우 생성
	_hWnd = CreateWindow(
		WINNAME,				//윈도우 클래스 이름
		WINNAME,				//윈도우 타이틀바에 나타낼 문자열
		WS_OVERLAPPEDWINDOW,	//윈도우 스타일
		WINSTARTX,				//윈도우 창 시작 X좌표
		WINSTARTY,				//윈도우 창 시작 Y좌표
		WINSIZEX,				//윈도우 가로크기
		WINSIZEY,				//윈도우 세로크기
		NULL,					//부모 윈도우 유무
		(HMENU)NULL,			//메뉴핸들
		hInstance,				//인스턴스 윈도우 지정
		NULL);

	//클라이언트 영역이 재설정 되었음.
	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
#endif


	//화면에 윈도우 보여준다
	ShowWindow(_hWnd, cmdShow);

	//mainGame 초기화
	if (FAILED(_mg.init()))
	{
		//메인게임이 초기화 실패하면 바로 종료시킴

		return 0;
	}

	
	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60.0F);
			_mg.update();
			_mg.render();
		}

	}
	
	
	/*
	//메세지 루프
	while (GetMessage(&message, 0, 0, 0))
	{

		TranslateMessage(&message);	//키보드 입력 메시지 처리를 담당
		DispatchMessage(&message);	//실제로 윈도우로 전달해 준다
	}
	*/
	//메시지 다 돈 후 해제
	_mg.release();

	//등록해준 클라스해제
	UnregisterClass(WINNAME, hInstance);


	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg.MainProc(hWnd, iMessage, wParam, lParam);

}

void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	//비작업 영역을 제외한 작업 영역안을 특정 크기로 맞춰준다
	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);

}