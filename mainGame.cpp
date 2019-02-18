#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}

/////////////////////////////////////////////////
//    �����ڿ� �Ҹ��ڴ� ���� �Ⱦ���
/////////////////////////////////////////////////


//�ʱ�ȭ ���ִ� ��
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	SCENEMANAGER->addScene("tankScene", new aStarTestScene);

	SCENEMANAGER->changeScene("tankScene");

	return S_OK;
}

//�����Ҵ� �� �޸� ���� ���ִ� ��
void mainGame::release(void)
{
	gameNode::release();
}

//���� �ϴ� ��
void mainGame::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();
}

//�׷��ִ� ��
void mainGame::render(void)
{
	//�ڿ� ��� ��ȭ���� ����ش�
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	//������� ������ ȭ�鿡 �׸��� # ������ �� �� #
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
