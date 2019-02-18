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

//�������� ����� �̻��� Missile Public Frame
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


//�⺻���� ��ΰ� ���� �Ѿ�(�⺻�Ѿ� == �÷��̾ ���� �ʵ����� �� ��� �ִ� �Ѿ�)
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

	//���� �Ѿ� �߻� �Լ�
	void fire(float x, float y, float angle, float speed);

	void move();
	void draw();

	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet(void) { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet(void) { return _viBullet; }


	bullet();
	~bullet();
};


//������ �س��� �� �̻���
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
//�߻��Ҷ� �����ؼ� �� �̻���
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

	//�߽� �Ծ�
	void fire(float x, float y);

	void move();

	//������ ���� �Լ�
	void removeMissile(int arrNum);

	//�Ѿ� ���Ͱ����Ͽ� ������ ������ ����� (�浹�� ����!)
	vector<tagBullet> getVBullet(void) { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet(void) { return _viBullet; }


	daepodong();
	~daepodong();
};