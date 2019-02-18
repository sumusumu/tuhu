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
	//���Ⱑ ���� ����Ʈ
	//��ũ�� ���������°� ������ �Ϻ�
	RECT rcCollision;

	//�˻��� Ÿ��
	int tileIndex[2];
	int tileX, tileY;

	//������ ������ ��������
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


	//���� ����(��ũ��) ��� �ִ� Ÿ���� �ε��� ��ȣ ��������
	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;


	//�浹��Ʈ�� ���� ����ָ� �ξ� �����ϴ�
	rcCollision.left += 2;
	rcCollision.top += 2;
	rcCollision.right -= 2;
	rcCollision.bottom -= 2;

	//�߰���غ��ÿ�
	//��ũ ���̷��ǿ� ���� �����ִ� Ÿ������ �ƴ��� 
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

	//������ Ÿ�� �����ش�
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
	//1p ��ũ ������

	_rc = _tankMap->getTiles()[_tankMap->getPosFirst()].rc;

	_x = _rc.left + (_rc.right - _rc.left) / 2;
	_y = _rc.top + (_rc.bottom - _rc.top) / 2;

}