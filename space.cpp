#include "stdafx.h"
#include "space.h"


space::space()
{
}


space::~space()
{
}

HRESULT space::init(void)
{
	//��׶��� �̹��� �־���
	_background = IMAGEMANAGER->findImage("background");

	//��ü �� ���� ������
	_mapSizeWidth = _background->getWidth();

	_mapSizeHeight = _background->getHeight();

	return S_OK;
}

void space::release(void)
{

}

void space::update(void)
{

}

void space::render(void)
{
	int x, y;
	DIRECTION direction;
	RECT rcSour[4];

	x = _ship->getRect().left - (WINSIZEX / 2 - _ship->getImage()->getFrameWidth() / 2);
	y = _ship->getRect().top - (WINSIZEY / 2 - _ship->getImage()->getFrameHeight() / 2);

	//������ �������� ���� �ٿ��ش�
	x = x % _mapSizeWidth;
	y = y % _mapSizeHeight;

	if (x <= -WINSIZEX) x += _mapSizeWidth;
	if (y <= -WINSIZEY) y += _mapSizeHeight;

	//����~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	direction = getDirection(x, y);

	/*
	DIRECTION_LEFT_TOP,
	DIRECTION_MIDDLE_TOP,
	DIRECTION_RIGHT_TOP,
	DIRECTION_LEFT_MIDDLE,
	DIRECTION_MIDDLE_MIDDLE,
	DIRECTION_RIGHT_MIDDLE,
	DIRECTION_LEFT_BOTTOM,
	DIRECTION_MIDDLE_BOTTOM,
	DIRECTION_RIGHT_BOTTOM
	*/

	if (direction == DIRECTION_RIGHT_MIDDLE)
	{
		x -= _mapSizeWidth;
		direction = DIRECTION_LEFT_MIDDLE;
	}
	if (direction == DIRECTION_MIDDLE_BOTTOM)
	{
		y -= _mapSizeHeight;
		direction = DIRECTION_MIDDLE_TOP;
	}
	if (direction == DIRECTION_RIGHT_TOP)
	{
		x -= _mapSizeWidth;
		direction = DIRECTION_LEFT_TOP;
	}
	if (direction == DIRECTION_LEFT_BOTTOM)
	{
		y -= _mapSizeHeight;
		direction = DIRECTION_LEFT_TOP;
	}
	if (direction == DIRECTION_RIGHT_BOTTOM)
	{
		x -= _mapSizeWidth;
		y -= _mapSizeHeight;
		direction = DIRECTION_LEFT_TOP;
	}


	switch (direction)
	{
	case DIRECTION_LEFT_TOP:
		rcSour[0] = RectMake(_mapSizeWidth + x, _mapSizeHeight + y, _mapSizeWidth, _mapSizeHeight);
		rcSour[1] = RectMake(0, _mapSizeHeight + y, WINSIZEX + x, _mapSizeHeight);
		rcSour[2] = RectMake(_mapSizeWidth + x, 0, _mapSizeWidth, WINSIZEY + y);
		rcSour[3] = RectMake(0, 0, WINSIZEX + x, WINSIZEY + y);

		_background->render(getMemDC(), 0, 0, rcSour[0].left, rcSour[0].top,
			rcSour[0].right - rcSour[0].left,
			rcSour[0].bottom - rcSour[0].top);

		_background->render(getMemDC(), -x, 0, rcSour[1].left, rcSour[1].top,
			rcSour[1].right - rcSour[1].left,
			rcSour[1].bottom - rcSour[1].top);

		_background->render(getMemDC(), 0, -y, rcSour[2].left, rcSour[2].top,
			rcSour[2].right - rcSour[2].left,
			rcSour[2].bottom - rcSour[2].top);

		_background->render(getMemDC(), -x, -y, rcSour[3].left, rcSour[3].top,
			rcSour[3].right - rcSour[3].left,
			rcSour[3].bottom - rcSour[3].top);

		break;
	case DIRECTION_MIDDLE_TOP:
		rcSour[0] = RectMake(x, _mapSizeHeight + y, x + WINSIZEX, _mapSizeHeight);
		rcSour[1] = RectMake(x, 0, WINSIZEX + x, WINSIZEY + y);

		_background->render(getMemDC(), 0, 0, rcSour[0].left, rcSour[0].top,
			rcSour[0].right - rcSour[0].left,
			rcSour[0].bottom - rcSour[0].top);

		_background->render(getMemDC(), 0, -y, rcSour[1].left, rcSour[1].top,
			rcSour[1].right - rcSour[1].left,
			rcSour[1].bottom - rcSour[1].top);

		break;
	case DIRECTION_LEFT_MIDDLE:
		rcSour[0] = RectMake(_mapSizeWidth + x, y, _mapSizeWidth, _mapSizeHeight + y);
		rcSour[1] = RectMake(0, y, WINSIZEX + x, WINSIZEY + y);

		_background->render(getMemDC(), 0, 0, rcSour[0].left, rcSour[0].top,
			rcSour[0].right - rcSour[0].left,
			rcSour[0].bottom - rcSour[0].top);

		_background->render(getMemDC(), -x, 0, rcSour[1].left, rcSour[1].top,
			rcSour[1].right - rcSour[1].left,
			rcSour[1].bottom - rcSour[1].top);

		break;
	case DIRECTION_MIDDLE_MIDDLE:
		rcSour[0] = RectMake(x, y, WINSIZEX + x, WINSIZEY + y);


		_background->render(getMemDC(), 0, 0, rcSour[0].left, rcSour[0].top,
			rcSour[0].right - rcSour[0].left,
			rcSour[0].bottom - rcSour[0].top);

		break;
	}

}

DIRECTION space::getDirection(int x, int y)
{
	int direction = 0;

	//�¿� �̵� ����
	if (0 < x && x + WINSIZEX <= _mapSizeWidth)
	{
		direction++;
	}

	//����Ʈ ����
	if (_mapSizeWidth <= x + WINSIZEX)
	{
		direction += 2;
	}

	//�� �Ʒ� �̵�
	if (0 < y && y + WINSIZEY <= _mapSizeHeight)
	{
		direction += 3;
	}

	//�Ʒ�
	if (_mapSizeHeight < y + WINSIZEY)
	{
		direction += 6;
	}

	return DIRECTION(direction);
}