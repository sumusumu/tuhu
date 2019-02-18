#pragma once
#include "gameNode.h"
#include "jump.h"

// ��� �̵��ӵ� ������
#define SPEED 2.5f

enum KNIGHTDIRECTION
{
	KNIGHTDIRECTION_RIGHT_STOP,
	KNIGHTDIRECTION_LEFT_STOP,
	KNIGHTDIRECTION_RIGHT_MOVE,
	KNIGHTDIRECTION_LEFT_MOVE,
	KNIGHTDIRECTION_RIGHT_SIT,
	KNIGHTDIRECTION_LEFT_SIT,
	KNIGHTDIRECTION_RIGHT_FIRE,
	KNIGHTDIRECTION_LEFT_FIRE,
	KNIGHTDIRECTION_RIGHT_SIT_FIRE,
	KNIGHTDIRECTION_LEFT_SIT_FIRE,
	KNIGHTDIRECTION_RIGHT_JUMP,
	KNIGHTDIRECTION_LEFT_JUMP,
	KNIGHTDIRECTION_RIGHT_MOVE_JUMP,
	KNIGHTDIRECTION_LEFT_MOVE_JUMP
};

class knight : public gameNode
{
private:
	KNIGHTDIRECTION _knightDirection;

	//����Ʈ �̹��� �� ��ǥ
	image* _image;
	float _x;
	float _y;

	RECT _rc;

	jump* _jump;
	//�̹��� �������� �ִϸ��̼�
	animation* _knightMotion;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�ݹ��� �ϱ� ����
	static void rightFire(void* obj);
	static void leftFire(void* obj);
	static void rightSitFire(void* obj);
	static void leftSitFire(void* obj);

	static void rightJump(void* obj);
	static void leftJump(void* obj);
	static void rightMoveJump(void* obj);
	static void leftMoveJump(void* obj);
	

	//���� �ݹ鵵 �غ���(�ʼ��ƴ�)

	//���� ��� ���� ������ �Ծ���
	KNIGHTDIRECTION getKnightDirection(void) { return _knightDirection; }
	void setKnightDirection(KNIGHTDIRECTION direction) { _knightDirection = direction; }

	animation* getKnightMotion(void) { return _knightMotion; }
	void setKnightMotion(animation* ani) { _knightMotion = ani; }
	
	knight();
	~knight();
};

