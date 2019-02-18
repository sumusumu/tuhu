#pragma once
#include "gameNode.h"
#include "tankMap.h"

//��ũ ������ ����
enum TANKDIRECTION
{
	TANKDIRECTION_LEFT,
	TANKDIRECTION_UP,
	TANKDIRECTION_RIGHT,
	TANKDIRECTION_DOWN
};

class tank : public gameNode
{
private:
	tankMap* _tankMap;

	TANKDIRECTION _direction;

	image* _image;
	RECT _rc;

	float _x, _y;
	float _speed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void tankMove(void);
	void setTankPosition(void);

	void setTankMapMemoryAddressLink(tankMap* tm) { _tankMap = tm; }


	tank();
	~tank();
};

