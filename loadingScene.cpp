#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init(void)
{
	_loading = new loading;
	_loading->init();

	char image[256];

	//로딩을 한번 해봅시다
	for (int i = 0; i < 50; i++)
	{
		memset(image, 0, sizeof(image));
		sprintf(image, "selectCh%d", i);
		_loading->loadImage(image, "selectCh.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	}

	return S_OK;
}

void loadingScene::release(void)
{
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	_loading->update();

	if (!_loading->loadNext())
	{
		SCENEMANAGER->changeScene("선택씬");
	}
}

void loadingScene::render(void)
{
	_loading->render();
}