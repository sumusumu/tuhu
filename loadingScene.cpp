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

	//�ε��� �ѹ� �غ��ô�
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
		SCENEMANAGER->changeScene("���þ�");
	}
}

void loadingScene::render(void)
{
	_loading->render();
}