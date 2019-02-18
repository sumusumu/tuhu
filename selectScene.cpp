#include "stdafx.h"
#include "selectScene.h"


selectScene::selectScene()
{
}


selectScene::~selectScene()
{
}

HRESULT selectScene::init()
{
	/*
	_btnScene = new button;
	_btnScene->init("button", WINSIZEX / 2, WINSIZEY / 2,
		PointMake(0, 0), PointMake(0, 1), sceneChange);
		*/
	_btnAngleUp = new button;
	_btnAngleUp->init("button", WINSIZEX / 2 - 200,
		WINSIZEY / 2 + 100, PointMake(0, 0),
		PointMake(0, 1), cbAngleUp);

	_btnAngleDown = new button;
	_btnAngleDown->init("button", WINSIZEX / 2 + 200,
		WINSIZEY / 2 + 100, PointMake(0, 0),
		PointMake(0, 1), cbAngleDown);


	return S_OK;
}

void selectScene::release()
{

}

void selectScene::update()
{
	//_btnScene->update();

	_btnAngleUp->update();
	_btnAngleDown->update();
}

void selectScene::render()
{

	//_btnScene->render();
	_btnAngleUp->render();
	_btnAngleDown->render();

	char str[128];

	sprintf(str, "ΩÏ∑∫∆Æ æ¿");
	TextOut(getMemDC(), WINSIZEX / 2 - 200, WINSIZEY / 2 - 100, str, strlen(str));
}

void selectScene::cbAngleUp(void)
{
	DATABASE->setElementDataAngle("battle", DATABASE->getElementData("battle")->angle + 0.1f);
}

void selectScene::cbAngleDown(void)
{
	DATABASE->setElementDataAngle("battle", DATABASE->getElementData("battle")->angle - 0.1f);
}

/*
void selectScene::sceneChange()
{
	SCENEMANAGER->changeScene("∞‘¿”æ¿");
}
*/