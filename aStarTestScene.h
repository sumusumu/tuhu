#pragma once
#include "gameNode.h"
#include "aStarTest.h"

class aStarTestScene : public gameNode
{
private:
	aStarTest* _aStarTest;
public:
	HRESULT init(void);
	void release();
	void update();
	void render();



	aStarTestScene();
	~aStarTestScene();
};

