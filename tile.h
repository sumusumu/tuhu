#pragma once
#include "gameNode.h"
#include <string>

class tile : public gameNode
{
private:
	int _idX;
	int _idY;

	POINT _center;
	RECT _rc;

	float _totalCost;		// f = g + h
	float _costFromStart;	// g : 시작점부터 현재 노드까지 경로비용
	float _costToGoal;		// h : 현재 노드부터 끝점까지 경로비용

	bool _isOpen;

	tile* _parentNode;

	COLORREF _color;
	HBRUSH _brush;
	HPEN _pen;

	string _attribute;

public:
	virtual HRESULT init(int idX, int idY);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	int getIdX(void) { return _idX; }
	int getIdY(void) { return _idY; }

	void setColor(COLORREF color)
	{
		DeleteObject(_brush);
		_color = color;
		_brush = CreateSolidBrush(_color);
	}

	RECT getRect(void) { return _rc; }

	void setCenter(POINT center) { _center = center; }
	POINT getCenter(void) { return _center; }

	void setAttribute(string str) { _attribute = str; }
	string getAttribute(void) { return _attribute; }

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost(void) { return _totalCost; }

	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart(void) { return _costFromStart; }

	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal(void) { return _costToGoal; }

	void setParentNode(tile* t) { _parentNode = t; }
	tile* getParentNode(void) { return _parentNode; }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen(void) { return _isOpen; }

	tile();
	~tile();
};

