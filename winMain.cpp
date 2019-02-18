//��������� ����Ѵ�
#include "stdafx.h"
#include "mainGame.h"

//==============================================
// - 2015. 06. 30 - ## ���������� ����� �����Ѵ� ##
//==============================================
HINSTANCE _hInstance;
HWND _hWnd;

//���콺 ��ǥ
POINT _ptMouse;

mainGame _mg;

BOOL _leftButtonDown = FALSE;
BOOL _rightButtonDown = FALSE;

//==============================================
// - 2015. 06. 30 - ## �Լ� ������ Ÿ�� ���� ##
//==============================================

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowsSize(int x, int y, int width, int height);


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;		//�ü������ �߻��ϴ� �޽��� ������ �����ϱ� ���� ����ü(����)
	WNDCLASS wndClass;	//�������� ������ �����ϱ� ���� ����ü ����

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;										//Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;										//������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ ��׶��� ����
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//������ Ŀ��
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//������ ������
	wndClass.hInstance = hInstance;									//������ �ν��Ͻ�
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//���ν���
	wndClass.lpszClassName = WINNAME;								//Ŭ���� �̸�
	wndClass.lpszMenuName = NULL;									//�޴��̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ ������~

	//������ Ŭ���� ���
	RegisterClass(&wndClass);


#ifdef FULLSCREEN
	DEVMODE dm;

	ZeroMemory(&dm, sizeof(DEVMODE));

	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = 32;
	dm.dmPelsWidth = 1024;
	dm.dmPelsHeight = 768;
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	//���� �ػ󵵷� �ǵ�����
	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}

	//������ ����
	_hWnd = CreateWindow(
		WINNAME,						//������ Ŭ���� �̸�
		WINNAME,						//������ Ÿ��Ʋ�ٿ� ��Ÿ�� ���ڿ�
		WS_POPUPWINDOW | WS_MAXIMIZE,	//������ ��Ÿ��
		WINSTARTX,						//������ â ���� X��ǥ
		WINSTARTY,						//������ â ���� Y��ǥ
		GetSystemMetrics(SM_CXSCREEN),	//������ ����ũ��
		GetSystemMetrics(SM_CYSCREEN),	//������ ����ũ��
		NULL,							//�θ� ������ ����
		(HMENU)NULL,					//�޴��ڵ�
		hInstance,						//�ν��Ͻ� ������ ����
		NULL);

	//Ŭ���̾�Ʈ ������ �缳�� �Ǿ���.
	setWindowsSize(WINSTARTX, WINSTARTY, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
#else
	//������ ����
	_hWnd = CreateWindow(
		WINNAME,				//������ Ŭ���� �̸�
		WINNAME,				//������ Ÿ��Ʋ�ٿ� ��Ÿ�� ���ڿ�
		WS_OVERLAPPEDWINDOW,	//������ ��Ÿ��
		WINSTARTX,				//������ â ���� X��ǥ
		WINSTARTY,				//������ â ���� Y��ǥ
		WINSIZEX,				//������ ����ũ��
		WINSIZEY,				//������ ����ũ��
		NULL,					//�θ� ������ ����
		(HMENU)NULL,			//�޴��ڵ�
		hInstance,				//�ν��Ͻ� ������ ����
		NULL);

	//Ŭ���̾�Ʈ ������ �缳�� �Ǿ���.
	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
#endif


	//ȭ�鿡 ������ �����ش�
	ShowWindow(_hWnd, cmdShow);

	//mainGame �ʱ�ȭ
	if (FAILED(_mg.init()))
	{
		//���ΰ����� �ʱ�ȭ �����ϸ� �ٷ� �����Ŵ

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
	//�޼��� ����
	while (GetMessage(&message, 0, 0, 0))
	{

		TranslateMessage(&message);	//Ű���� �Է� �޽��� ó���� ���
		DispatchMessage(&message);	//������ ������� ������ �ش�
	}
	*/
	//�޽��� �� �� �� ����
	_mg.release();

	//������� Ŭ������
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

	//���۾� ������ ������ �۾� �������� Ư�� ũ��� �����ش�
	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);

}