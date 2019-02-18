#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

//초기화 해주는 함수
HRESULT gameNode::init(void)
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;
	
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);

		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		EFFECTMANAGER->init();
		SOUNDMANAGER->init();
		SCENEMANAGER->init();
		KEYANIMANAGER->init();
		TXTDATA->init();
		DATABASE->init();
	}

	return S_OK;
}

//메모리 해제 해주는 함수
void gameNode::release(void)
{
	
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);

		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->releaseSingleton();
		EFFECTMANAGER->releaseSingleton();
		SCENEMANAGER->releaseSingleton();
		SOUNDMANAGER->releaseSingleton();
		KEYANIMANAGER->releaseSingleton();
		TXTDATA->releaseSingleton();
		DATABASE->releaseSingleton();
	}

	//DC릴리즈
	ReleaseDC(_hWnd, _hdc);
	
}

//연산 담당 함수
void gameNode::update(void)
{
	
}

//그려주는 함수
void gameNode::render()
{

}




LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (iMessage)
	{
		//초기화는 여기에!
		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
		
			this->render();

			EndPaint(hWnd, &ps);
		}
		break;
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));
		break;
		case WM_LBUTTONDOWN:
			_leftButtonDown = true;
			
		break;
		case WM_LBUTTONUP:
			_leftButtonDown = false;
		break;
		case WM_RBUTTONDOWN:
			_rightButtonDown = true;
		break;
		case WM_RBUTTONUP:
			_rightButtonDown = false;
		break;

		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
					PostMessage(hWnd, WM_DESTROY, 0, 0);
				break;
			}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
		return 0;

	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}