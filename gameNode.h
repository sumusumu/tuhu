#pragma once
#include "image.h"

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

//컨트롤 박스 사용을 위한 이넘문
enum CTRL
{
	CTRL_SAVE, CTRL_LOAD, CTRL_TERRAINDRAW,
	CTRL_OBJDRAW, CTRL_ERASER, CTRL_END
};

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:

	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render();

	image* getBackBuffer(void) { return _backBuffer; }
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }
	
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	

	gameNode();
	virtual ~gameNode();
};

