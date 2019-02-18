#pragma once
#include "tileNode.h"
#include "gameNode.h"

class tankMap : public gameNode
{
private:

	tagTile _tiles[TILEX * TILEY];
	DWORD _attribute[TILEX * TILEY];

	int _pos[2];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//¸Ê ·Îµå
	void load(void);

	tagTile* getTiles(void) { return _tiles; }
	int getPosFirst(void) { return _pos[0]; }
	int getPosSecond(void) { return _pos[1]; }

	DWORD* getAttribute(void) { return _attribute; }

	tankMap();
	~tankMap();
};

