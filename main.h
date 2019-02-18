#pragma once
#include "gameNode.h"
#include "tankScene.h"
#include "aStarTestScene.h"


class main : public gameNode
{
private:

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);



	main();
	~main();
};

