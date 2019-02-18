#pragma once
#include "gameNode.h"
#include "jump.h"

// 기사 이동속도 디파인
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

	//나이트 이미지 및 좌표
	image* _image;
	float _x;
	float _y;

	RECT _rc;

	jump* _jump;
	//이미지 움직여줄 애니메이션
	animation* _knightMotion;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//콜백을 하기 위함
	static void rightFire(void* obj);
	static void leftFire(void* obj);
	static void rightSitFire(void* obj);
	static void leftSitFire(void* obj);

	static void rightJump(void* obj);
	static void leftJump(void* obj);
	static void rightMoveJump(void* obj);
	static void leftMoveJump(void* obj);
	

	//점프 콜백도 해볼것(필수아님)

	//현재 기사 방향 가져올 함쑤쑤
	KNIGHTDIRECTION getKnightDirection(void) { return _knightDirection; }
	void setKnightDirection(KNIGHTDIRECTION direction) { _knightDirection = direction; }

	animation* getKnightMotion(void) { return _knightMotion; }
	void setKnightMotion(animation* ani) { _knightMotion = ani; }
	
	knight();
	~knight();
};

