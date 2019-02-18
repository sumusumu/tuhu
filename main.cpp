#include "stdafx.h"
#include "main.h"


main::main()
{
}


main::~main()
{
}

/////////////////////////////////////////////////
//    생성자와 소멸자는 이제 안쓴다
/////////////////////////////////////////////////


//초기화 해주는 곳
HRESULT main::init(void)
{
	gameNode::init(true);

	SCENEMANAGER->addScene("tankScene", new aStarTestScene);

	SCENEMANAGER->changeScene("tankScene");

	return S_OK;
}

//동적할당 등 메모리 해제 해주는 곳
void main::release(void)
{
	gameNode::release();
}

//연산 하는 곳
void main::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();
}

//그려주는 곳
void main::render(void)
{
	//뒤에 흰색 도화지를 깔아준다
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	//백버퍼의 내용을 화면에 그린다 # 지우지 말 것 #
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
