#pragma once
#include "gameNode.h"

class jump : public gameNode
{
private:
	float _jumpPower;
	float _gravity;

	float* _x;
	float* _y;

	float _startX;
	float _startY;

	bool _isJumping;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void jumping(float* x, float* y, float power, float gravity);

	//�������̳� ���ο� ���� �� ����
	bool getIsJumping(void) { return _isJumping; }



	jump();
	~jump();
};

