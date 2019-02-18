#pragma once
#include "gameNode.h"

class saveLoadData : public gameNode
{
public:
	void update(void);

	void write(void);
	void read(void);

	


	saveLoadData();
	~saveLoadData();
};

