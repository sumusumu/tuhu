#include "stdafx.h"
#include "timeManager.h"


timeManager::timeManager()
	: _timer(NULL)
{
}


timeManager::~timeManager()
{
}

HRESULT timeManager::init(void)
{
	//Ÿ�̸� ����
	_timer = new timer;

	//Ÿ�̸� �ʱ�ȭ
	_timer->init();


	return S_OK;
}

void timeManager::release(void)
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
		_timer = NULL;
	}
}

void timeManager::update(float lock)
{
	if (_timer != NULL)
	{
		_timer->tick(lock);
	}
}

void timeManager::render(HDC hdc)
{
	char str[256];
	string strFrame;

	//���� �����(TRANSPARENT : ����, OPAQUE : ������)
	SetBkMode(hdc, TRANSPARENT);

	//���� ����
	SetTextColor(hdc, RGB(255, 255, 255));

#ifdef _DEBUG
	{
		if (_timer != NULL)
		{
			//������ �������
			//First Person Shooter == FPS
			wsprintf(str, "framePerSec : %d", _timer->getFrameRate());
			TextOut(hdc, 0, 0, str, strlen(str));

			//����Ÿ�� �������
			sprintf_s(str, "worldTime : %f", _timer->getWorldTime());
			TextOut(hdc, 0, 20, str, strlen(str));

			//���� tick �������
			sprintf_s(str, "elapsedTime : %f", _timer->getElapsedTime());
			TextOut(hdc, 0, 40, str, strlen(str));
		}
	}
#else
	{
		if(time != NULL)
		{
			//������ �������
			wsprintf(str, "framePerSec : %d", _timer->getFrameRate());
			TextOut(hdc, 0, 0, str, strlen(str));
		}
	}
#endif
}