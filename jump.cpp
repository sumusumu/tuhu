#include "stdafx.h"
#include "jump.h"


jump::jump()
{
}


jump::~jump()
{
}

HRESULT jump::init(void)
{
	_isJumping = false;

	_jumpPower = _gravity = 0.0f;

	return S_OK;
}

void jump::release(void)
{

}

void jump::update(void)
{
	if (!_isJumping) return;

	*_y -= _jumpPower;
	_jumpPower -= _gravity;

	if (_startY < *_y)
	{
		*_y = _startY;
		_isJumping = false;
	}


}

void jump::render(void)
{

}

void jump::jumping(float* x, float* y, float power, float gravity)
{
	if (_isJumping) return;

	_isJumping = true;

	_x = x;
	_y = y;

	_startX = *x;
	_startY = *y;

	_gravity = gravity;
	_jumpPower = power;

}
