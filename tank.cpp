#include "stdafx.h"
#include "tank.h"


tank::tank()
{
}


tank::~tank()
{
}

HRESULT tank::init(void)
{
	_direction = TANKDIRECTION_RIGHT;

	_image = IMAGEMANAGER->addFrameImage("tank", "tank.bmp", 0, 0, 256, 128, 8, 4, true, RGB(255, 0, 255));
	_speed = 100.0f;


	return S_OK;
}

void tank::release(void)
{

}

void tank::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_direction = TANKDIRECTION_LEFT;
		tankMove();
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_direction = TANKDIRECTION_RIGHT;
		tankMove();
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_direction = TANKDIRECTION_UP;
		tankMove();
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_direction = TANKDIRECTION_DOWN;
		tankMove();
	}


}

void tank::render(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top);
}

void tank::tankMove(void)
{
	//여기가 오늘 포인트
	//탱크를 움직여오는게 숙제의 일부
	RECT rcCollision;

	//검사할 타일
	int tileIndex[2];
	int tileX, tileY;

	//가상의 움직임 예상지역
	rcCollision = _rc;



	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * _speed;

	switch (_direction)
	{
		case TANKDIRECTION_LEFT:
			_image->setFrameX(0);
			_image->setFrameY(3);
			_x -= moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(),
				_image->getFrameHeight());
		break;
		case TANKDIRECTION_UP:
			_image->setFrameX(0);
			_image->setFrameY(0);
			_y -= moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(),
				_image->getFrameHeight());
		break;
		case TANKDIRECTION_RIGHT:
			_image->setFrameX(0);
			_image->setFrameY(2);
			_x += moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(),
				_image->getFrameHeight());
		break;
		case TANKDIRECTION_DOWN:
			_image->setFrameX(0);
			_image->setFrameY(1);
			_y += moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(),
				_image->getFrameHeight());
		break;

	}


	//현재 내가(탱크가) 밟고 있는 타일의 인덱스 번호 가져오기
	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;


	//충돌렉트를 조금 깍아주면 훨씬 수월하다
	rcCollision.left += 2;
	rcCollision.top += 2;
	rcCollision.right -= 2;
	rcCollision.bottom -= 2;

	//잘계산해보시오
	//탱크 다이렉션에 대한 갈수있는 타일인지 아닌지 
	//
	switch (_direction)
	{
		case TANKDIRECTION_LEFT:
			tileIndex[0] = tileX + tileY * TILEX;
			tileIndex[1] = tileX + (tileY + 1) * TILEX;
		break;
		case TANKDIRECTION_UP:
			tileIndex[0] = tileX + tileY * TILEY;
			tileIndex[1] = tileX + 1 + tileY * TILEX;
		break;
		case TANKDIRECTION_RIGHT:
			tileIndex[0] = tileX + tileY * TILEX + 1;
			tileIndex[1] = (tileX + (tileY + 1) * TILEX) + 1;
		break;
		case TANKDIRECTION_DOWN:
			tileIndex[0] = (tileX + tileY * TILEX) + TILEX;
			tileIndex[1] = (tileX + 1 + tileY * TILEX) + TILEX;
		break;
	}

	//못가는 타일 막아준다
	for (int i = 0; i < 2; i++)
	{
		RECT rc;
		if (((_tankMap->getAttribute()[tileIndex[i]] & ATTR_UNMOVAL) == ATTR_UNMOVAL) &&
			IntersectRect(&rc, &_tankMap->getTiles()[tileIndex[i]].rc, &rcCollision))
		{

			switch (_direction)
			{
				case TANKDIRECTION_LEFT:
					_rc.left = _tankMap->getTiles()[tileIndex[i]].rc.right;
					_rc.right = _rc.left + 30;
					_x = _rc.left + (_rc.right - _rc.left) / 2;
				break;
				case TANKDIRECTION_UP:
					_rc.top = _tankMap->getTiles()[tileIndex[i]].rc.bottom;
					_rc.bottom = _rc.top + 30;
					_y = _rc.top + (_rc.bottom - _rc.top) / 2;
				break;
				case TANKDIRECTION_RIGHT:
					_rc.right = _tankMap->getTiles()[tileIndex[i]].rc.left;
					_rc.left = _rc.right - 30;
					_x = _rc.left + (_rc.right - _rc.left) / 2;
				break;
				case TANKDIRECTION_DOWN:
					_rc.bottom = _tankMap->getTiles()[tileIndex[i]].rc.top;
					_rc.top = _rc.bottom - 30;
					_y = _rc.top + (_rc.bottom - _rc.top) / 2;
				break;

			}
			return;
		}
		
	}
	

	rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(),
		_image->getFrameHeight());

	_rc = rcCollision;
	
}

void tank::setTankPosition(void)
{
	//1p 탱크 포지션

	_rc = _tankMap->getTiles()[_tankMap->getPosFirst()].rc;

	_x = _rc.left + (_rc.right - _rc.left) / 2;
	_y = _rc.top + (_rc.bottom - _rc.top) / 2;

}