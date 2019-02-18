#pragma once
#include "gameNode.h"
#include "button.h"

class selectScene : public gameNode
{
private:
//	button* _btnScene;

	button* _btnAngleUp;
	button* _btnAngleDown;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	static void cbAngleUp(void);
	static void cbAngleDown(void);


	//static void sceneChange();


	selectScene();
	~selectScene();
};

