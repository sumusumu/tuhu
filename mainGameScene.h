#pragma once
#include "gameNode.h"
class mainGameScene : public gameNode
{
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);


	mainGameScene();
	~mainGameScene();
};

