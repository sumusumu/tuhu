#include "stdafx.h"
#include "main.h"


main::main()
{
}


main::~main()
{
}

/////////////////////////////////////////////////
//    �����ڿ� �Ҹ��ڴ� ���� �Ⱦ���
/////////////////////////////////////////////////


//�ʱ�ȭ ���ִ� ��
HRESULT main::init(void)
{
	gameNode::init(true);

	SCENEMANAGER->addScene("testScene", new testScene);

	SCENEMANAGER->changeScene("testScene");

	return S_OK;
}

//�����Ҵ� �� �޸� ���� ���ִ� ��
void main::release(void)
{
	gameNode::release();
}

//���� �ϴ� ��
void main::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();
}

//�׷��ִ� ��
void main::render(void)
{
	//�ڿ� ��� ��ȭ���� ����ش�
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	//������� ������ ȭ�鿡 �׸��� # ������ �� �� #
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
