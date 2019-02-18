#include "stdafx.h"
#include "aStarTest.h"


aStarTest::aStarTest()
{
}


aStarTest::~aStarTest()
{
}

HRESULT aStarTest::init(void)
{
	//타일셋튕
	setTiles();

	_count = _start = 0;


	return S_OK;
}


void aStarTest::setTiles(void)
{
	//시작 타일 및 끝타일 설정을 해줌
	_startTile = new tile;
	_startTile->init(4, 12);
	_startTile->setAttribute("start");

	_endTile = new tile;
	_endTile->init(20, 12);
	_endTile->setAttribute("end");

	//현재 타일을 시작타일로 설정
	_currentTile = _startTile;

	//타일 초기화
	for (int i = 0; i < TILENUMY; i++)
	{
		for (int j = 0; j < TILENUMX; j++)
		{
			//시작타일
			if (j == _startTile->getIdX() && i == _startTile->getIdY())
			{
				_startTile->setColor(RGB(0, 255, 255));
				_vTotalList.push_back(_startTile);
				continue;
			}

			//끝타일
			if (j == _endTile->getIdX() && i == _endTile->getIdY())
			{
				_endTile->setColor(RGB(10, 120, 55));
				_vTotalList.push_back(_endTile);
				continue;
			}

			//그 외 타일이면
			tile* node = new tile;
			node->init(j, i);
			_vTotalList.push_back(node);
		}
	}
}

//가야할 길을 찾아서 벡터로 반환해주는 함수
vector<tile*> aStarTest::addOpenList(tile* currentTile)
{
	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	//현재 노드에서 주변을 확장하며 검사
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tile* node = _vTotalList[(startY * TILENUMX) + startX + j + (i * TILENUMX)];
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;

			node->setParentNode(_currentTile);

			bool addObj = true;

			//갈수 있는 길은 모두 오픈리스트에 넣어준다
			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			//검색한 타일의 색상을 바꿔준다
			if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));

			if (!addObj) continue;
			_vOpenList.push_back(node);
		}
	}

	return _vOpenList;
}

//길찾기
void aStarTest::pathFinder(tile* currentTile)
{
	//비교할 값 한타일의 중점과 다음 타일의 중점 사이의 값은 32
	float tempTotalCost = 50000;
	tile* tempTile;

	for (int i = 0; i < addOpenList(currentTile).size(); i++)
	{
		//현재 노드부터 끝점까지의 경로비용 계산
		_vOpenList[i]->setCostToGoal((abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) +
			abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		//시작점부터 현재 노드까지의 경로 비용
		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();
		_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > TILEWIDTH) ? 14 : 10);

		//총 비용 계솬 f = g + h
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() +
			_vOpenList[i]->getCostFromStart());

		//가장 비용이 저렴한 타일을 뽑느다(최단거리를 찾는다)
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		//갈 수 있는 길은 모두 오픈리스트에 역시 담아준다
		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{

			if (*_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}

		_vOpenList[i]->setIsOpen(false);
		if (!addObj) continue;
		_vOpenList.push_back(tempTile);
	}

	//목적지에 다 왔으면 리턴
	if (tempTile->getAttribute() == "end")
	{
		while (_currentTile->getParentNode() != NULL)
		{
			_currentTile->setColor(RGB(22, 14, 128));
			_currentTile = _currentTile->getParentNode();
		}

		return;
	}

	//현재 타일(지나온 경로)는 클로즈 리스트로!
	_vCloseList.push_back(tempTile);

	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;

	//재귀함쑤 찾을때까지 계속 돌린다
	//pathFinder(_currentTile);
}

void aStarTest::release(void)
{

}



void aStarTest::update(void)
{
	//시작버튼은 s로!
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		//pathFinder(_currentTile);
		_start = true;
	}

	if (_start)
	{
		_count++;

		if (_count % 5 == 0)
		{
			pathFinder(_currentTile);
			_count = 0;
		}
	}


	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vTotalList.size(); i++)
		{
			if (PtInRect(&_vTotalList[i]->getRect(), _ptMouse))
			{
				if (_vTotalList[i]->getAttribute() == "start") continue;
				if (_vTotalList[i]->getAttribute() == "end") continue;

				_vTotalList[i]->setIsOpen(false);
				_vTotalList[i]->setAttribute("wall");
				_vTotalList[i]->setColor(RGB(230, 140, 200));
				break;
			}
		}
	}
}

void aStarTest::render(void)
{
	for (int i = 0; i < _vTotalList.size(); i++)
	{
		_vTotalList[i]->render();
	}
}
