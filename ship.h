#pragma once
#include "gameNode.h"
#include "bullets.h"

class ship : public gameNode
{
protected:
	//모든 우주선들의 기본이 되는 속성들
	image* _image;
	RECT _rc;
	float _x, _y;
	float _angle;
	float _speed;
	float _radius;

	bullet* _bullet;

public:
	virtual HRESULT init(const char* imageName, int x, int y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void draw(void);
	virtual void keyControl(void);
	virtual void move();

	virtual void bulletFire();
	virtual void bulletMove();
	virtual void bulletDraw();

	virtual void focusDraw(void);
	virtual void defaultDraw(RECT rcFocus);

	image* getImage(void) { return _image; }
	RECT getRect(void) { return _rc; }


	//접근자 생성자
	void setAngle(float angle) { _angle = angle; }
	float getAngle(void) { return _angle; }

	ship();
	virtual ~ship();
};

