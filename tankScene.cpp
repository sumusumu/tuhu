#include "stdafx.h"
#include "tankScene.h"


tankScene::tankScene()
{
}


tankScene::~tankScene()
{
}

HRESULT tankScene::init()
{
	_tankMap = new tankMap;
	_tankMap->init();

	_tank = new tank;
	_tank->init();
	_tank->setTankMapMemoryAddressLink(_tankMap);
	_tank->setTankPosition();

	return S_OK;
}

void tankScene::release()
{
	SAFE_DELETE(_tankMap);
	SAFE_DELETE(_tank);
}

void tankScene::update()
{
	_tankMap->update();
	_tank->update();

}

void tankScene::render()
{
	_tankMap->render();
	_tank->render();
}