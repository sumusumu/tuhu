#pragma once
#include "gameNode.h"
#include "main.h"

class mainScene : public gameNode
{
private:
	//test* _test;

public:
	HRESULT init(void);
	void release();
	void update();
	void render();



	mainScene();
	~mainScene();
};

