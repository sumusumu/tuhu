#include "stdafx.h"
#include "mainGameScene.h"


mainGameScene::mainGameScene()
{
}


mainGameScene::~mainGameScene()
{
}

HRESULT mainGameScene::init(void)
{

	return S_OK;
}

void mainGameScene::release(void)
{

}

void mainGameScene::update(void)
{

}

void mainGameScene::render(void)
{
	IMAGEMANAGER->findImage("selectCh0")->render(getMemDC(), 0, 0);
}
