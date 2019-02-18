#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>

#define TILEWIDTH 32
#define TILEHEIGHT 32

#define TILENUMX ((int)(WINSIZEX / TILEWIDTH))
#define TILENUMY ((int)(WINSIZEY / TILEHEIGHT))

class aStarTest : public gameNode
{
private:
	vector<tile*> _vTotalList;
	vector<tile*>::iterator _viTotalList;

	vector<tile*> _vOpenList;
	vector<tile*>::iterator _viOpenList;

	vector<tile*> _vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile;
	tile* _endTile;
	tile* _currentTile;

	int _count;
	bool _start;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void setTiles(void);

	//길찾기
	void pathFinder(tile* currentTile);

	//넓이 우선 탐색을 활용해 가야할 타일을 찾아서 벡터로 반환해줍시다
	vector<tile*> addOpenList(tile* currentTile);

	aStarTest();
	~aStarTest();
};

