#pragma once
#include "gameNode.h"
//#include "test.h"

class testScene : public gameNode
{
private:
	//test* _test;

public:
	HRESULT init(void);
	void release();
	void update();
	void render();



	testScene();
	~testScene();
};

