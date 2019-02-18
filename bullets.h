#pragma once
#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image* bulletImage;
	RECT rc;
	int radius;
	float angle;
	float x, y;
	float fireX, fireY;
	float speed;
	bool fire;
	int count;
};

//공용으로 사용할 미사일 Missile Public Frame
class missilePF : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);
	void move();
	void draw();

	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet(void) { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet(void) { return _viBullet; }

	missilePF();
	~missilePF();
};


//기본으로 모두가 가질 총알(기본총알 == 플레이어도 적도 너도나도 다 쏠수 있는 총알)
class bullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	//공용 총알 발사 함수
	void fire(float x, float y, float angle, float speed);

	void move();
	void draw();

	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet(void) { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet(void) { return _viBullet; }


	bullet();
	~bullet();
};


//장전을 해놓고 쏠 미사일
class missile : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;

public:
	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y);

	void move(void);

	missile();
	~missile();

};
//발사할때 생성해서 쏠 미사일
class daepodong : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	float _bulletMax;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//발쏴 함쑤
	void fire(float x, float y);

	void move();

	//대포동 삭제 함수
	void removeMissile(int arrNum);

	//총알 벡터관련하여 접근자 생성자 만든다 (충돌을 위해!)
	vector<tagBullet> getVBullet(void) { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet(void) { return _viBullet; }


	daepodong();
	~daepodong();
};