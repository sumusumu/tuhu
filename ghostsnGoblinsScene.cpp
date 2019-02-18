#include "stdafx.h"
#include "ghostsnGoblinsScene.h"


ghostsnGoblinsScene::ghostsnGoblinsScene()
{
}


ghostsnGoblinsScene::~ghostsnGoblinsScene()
{
}

HRESULT ghostsnGoblinsScene::init()
{
	_knight = new knight;
	_knight->init();

	return S_OK;
}

void ghostsnGoblinsScene::release()
{

}

void ghostsnGoblinsScene::update()
{
	_knight->update();
}

void ghostsnGoblinsScene::render()
{
	_knight->render();
}