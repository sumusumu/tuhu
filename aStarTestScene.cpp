#include "stdafx.h"
#include "aStarTestScene.h"


aStarTestScene::aStarTestScene()
{
}


aStarTestScene::~aStarTestScene()
{
}

HRESULT aStarTestScene::init(void)
{
	_aStarTest = new aStarTest;
	_aStarTest->init();

	return S_OK;
}

void aStarTestScene::release()
{

}

void aStarTestScene::update()
{
	_aStarTest->update();
}

void aStarTestScene::render()
{
	_aStarTest->render();
}