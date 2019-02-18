#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarForward = IMAGEMANAGER->addImage("barForward", "hpBarTop.bmp", x, y, width, height, true, RGB(255, 0, 255));
	_progressBarBack = IMAGEMANAGER->addImage("barBack", "hpBarBottom.bmp", x, y, width, height, true, RGB(255, 0, 255));

	_width = _progressBarForward->getWidth();

	return S_OK;
}

HRESULT progressBar::init(char* btnUpImageKeyName, char* btnDownImageKeyName,
	int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMakeCenter(x, y, width, height);

	char strUpName[128];
	char strDownName[128];

	ZeroMemory(strUpName, sizeof(strUpName));
	ZeroMemory(strDownName, sizeof(strDownName));

	sprintf(strUpName, "%s.bmp", btnUpImageKeyName);
	sprintf(strDownName, "%s.bmp", btnDownImageKeyName);

	_progressBarBack = IMAGEMANAGER->addImage(btnDownImageKeyName, strDownName, x, y, width, height, true, RGB(255, 0, 255));
	_progressBarForward = IMAGEMANAGER->addImage(btnUpImageKeyName, strUpName, x, y, width, height, true, RGB(255, 0, 255));

	_width = _progressBarForward->getWidth();


	return S_OK;
}

void progressBar::release(void)
{

}

void progressBar::update(void)
{
	_rcProgress = RectMakeCenter(_x, _y,
		_progressBarBack->getWidth(), _progressBarForward->getHeight());
}

void progressBar::render(void)
{
	/*
	IMAGEMANAGER->render("barBack", getMemDC(),
		_rcProgress.left + _progressBarBack->getWidth() / 2,
		_y + _progressBarBack->getHeight() / 2,
		0, 0,
		_progressBarBack->getWidth(), _progressBarBack->getHeight());

	IMAGEMANAGER->render("barForward", getMemDC(),
		_rcProgress.left + _progressBarForward->getWidth() / 2,
		_y + _progressBarForward->getHeight() / 2,
		0, 0,
		_width, _progressBarForward->getHeight());
		*/

	_progressBarBack->render(getMemDC(), _rcProgress.left, _y, 0, 0,
		_progressBarBack->getWidth(),
		_progressBarBack->getHeight());

	_progressBarForward->render(getMemDC(), _rcProgress.left, _y, 
		0, 0,
		_width,
		_progressBarForward->getHeight());


}

//체력바 게이지
void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBack->getWidth();
}