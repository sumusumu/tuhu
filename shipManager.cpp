#include "stdafx.h"
#include "shipManager.h"


shipManager::shipManager()
{
}


shipManager::~shipManager()
{
}

HRESULT shipManager::init(void)
{
	//1P
	_ship[SHIPKIND_BATTLE] = new battle;
	_ship[SHIPKIND_BATTLE]->init("battle", 0, 0);

	//2P
	_ship[SHIPKIND_BATTLE2] = new battle2;
	_ship[SHIPKIND_BATTLE2]->init("battle2", 200, 300);

	//포커스 맞춰줍시다
	_focusShip = _ship[SHIPKIND_BATTLE];

	_space = new space;
	_space->init();
	_space->setShip(_focusShip);

	return S_OK;
}

void shipManager::release(void)
{

}

void shipManager::update(void)
{
	//포커스 변환
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_focusShip = _ship[SHIPKIND_BATTLE];
		_space->setShip(_focusShip);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_focusShip = _ship[SHIPKIND_BATTLE2];
		_space->setShip(_focusShip);
	}

	for (int i = 0; i < SHIPKIND_END; i++)
	{
		_ship[i]->update();
	}

	_focusShip->keyControl();

}

void shipManager::render(void)
{
	_space->render();

	for (int i = 0; i < SHIPKIND_END; i++)
	{
		if (_focusShip == _ship[i])
		{
			_focusShip->focusDraw();
		}
		else
		{
			_ship[i]->defaultDraw(_focusShip->getRect());
		}
	}
}