#include "stdafx.h"
#include "knight.h"


knight::knight()
{
}


knight::~knight()
{
}

HRESULT knight::init(void)
{
	//Á¡Çª Å¬¶ó½º
	_jump = new jump;
	_jump->init();

	//ÀÌ¹ÌÁö µî·Ï
	_image = IMAGEMANAGER->addFrameImage("knight", "knight.bmp", 0, 0, 612, 312, 9, 4, true, RGB(255, 0, 255));

	//³ªÀÌÆ® ¹æÇâ ÃÊ±âÈ­
	_knightDirection = KNIGHTDIRECTION_RIGHT_STOP;

	//ÁÂÇ¥ ¼ÂÆÃ
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	//¾Ö´Ï¸ŞÀÌ¼Ç µî·ÏÇØÁÜ
	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("knightRightStop", "knight", rightStop, 1, 6, true);

	int leftStop[] = { 9 };
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftStop", "knight", leftStop, 1, 6, true);

	//¹«ºù ¾Ö´Ï¸ŞÀÌ¼Ç
	int rightMove[] = { 1, 2, 3, 4, 5, 6 };
	KEYANIMANAGER->addArrayFrameAnimation("knightRightMove", "knight", rightMove, 6, 10, true);

	int leftMove[] = { 10, 11, 12, 13, 14, 15 };
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftMove", "knight", leftMove, 6, 10, true);

	//¾É±â ¾Ö´Ï¸ŞÀÌ¼ğ
	int rightSit[] = { 18 };
	KEYANIMANAGER->addArrayFrameAnimation("knightRightSit", "knight", rightSit, 1, 10, true);

	//¿ŞÂÊ ¾É±â
	int leftSit[] = { 27 };
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftSit", "knight", leftSit, 1, 10, true);

	//°ø°İ ¾Ö´Ï¸ŞÀÌ¼ğ
	int arrRightFire[] = { 7, 8 };
	KEYANIMANAGER->addArrayFrameAnimation("knightRightFire", "knight", arrRightFire, 2, 10, false, rightFire, this);

	int arrLeftFire[] = { 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftFire", "knight", arrLeftFire, 2, 10, false, leftFire, this);
	
	//¾É¾Æ¼­ °ø°İ
	int arrRightSitFire[] = { 19, 20 };
	KEYANIMANAGER->addArrayFrameAnimation("knightRightSitFire", "knight", arrRightSitFire, 2, 10, false, rightSitFire, this);

	int arrLeftSitFire[] = { 28, 29 };
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftSitFire", "knight", arrLeftSitFire, 2, 10, false, leftSitFire, this);

	//Á¦ÀÚ¸® Á¡ÇÁ
	int arrRightJump[] = { 22, 24, 25 };
	KEYANIMANAGER->addArrayFrameAnimation("knightRightJump", "knight", arrRightJump, 3, 4, false, rightJump, this);

	int arrLeftJump[] = { 31, 33, 34 };
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftJump", "knight", arrLeftJump, 3, 4, false, leftJump, this);
	
	//´Ş¸®´Ù Á¡ÇÁ
	int arrRightMoveJump[] = { 21, 23 };
	KEYANIMANAGER->addArrayFrameAnimation("knightRightMoveJump", "knight", arrRightMoveJump, 2, 3, false, rightMoveJump, this);

	int arrLeftMoveJump[] = { 30, 32 };
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftMoveJump", "knight", arrLeftMoveJump, 2, 3, false, leftMoveJump, this);

	_knightMotion = KEYANIMANAGER->findAnimation("knightRightStop");

	return S_OK;
}

void knight::release(void)
{

}

void knight::update(void)
{
	//¿À¸¥ÂÊÀ¸·Î ¹´¹´!
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_knightDirection = KNIGHTDIRECTION_RIGHT_MOVE;
		_knightMotion = KEYANIMANAGER->findAnimation("knightRightMove");
		_knightMotion->start();
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_knightDirection = KNIGHTDIRECTION_RIGHT_STOP;
		_knightMotion = KEYANIMANAGER->findAnimation("knightRightStop");
		_knightMotion->start();
	}

	//¿ŞÂÊÀ¸·Î ¹´¹´!
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_knightDirection = KNIGHTDIRECTION_LEFT_MOVE;
		_knightMotion = KEYANIMANAGER->findAnimation("knightLeftMove");
		_knightMotion->start();
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_knightDirection = KNIGHTDIRECTION_LEFT_STOP;
		_knightMotion = KEYANIMANAGER->findAnimation("knightLeftStop");
		_knightMotion->start();
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_jump->jumping(&_x, &_y, 8.0f, 0.4f);

		if (_knightDirection == KNIGHTDIRECTION_RIGHT_STOP)
		{
			_knightDirection = KNIGHTDIRECTION_RIGHT_JUMP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightJump");
			_knightMotion->start();
		}
		else if (_knightDirection == KNIGHTDIRECTION_LEFT_STOP)
		{
			_knightDirection = KNIGHTDIRECTION_LEFT_JUMP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightLeftJump");
			_knightMotion->start();
		}
		else if (_knightDirection == KNIGHTDIRECTION_RIGHT_MOVE)
		{
			_knightDirection = KNIGHTDIRECTION_RIGHT_MOVE_JUMP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightMoveJump");
			_knightMotion->start();
		}
		else if (_knightDirection == KNIGHTDIRECTION_LEFT_MOVE)
		{
			_knightDirection = KNIGHTDIRECTION_LEFT_MOVE_JUMP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightLeftMoveJump");
			_knightMotion->start();
		}
	}
	

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//¼­¼­ Ã¢ ´øÁö±â
		if (_knightDirection == KNIGHTDIRECTION_RIGHT_STOP ||
			_knightDirection == KNIGHTDIRECTION_RIGHT_MOVE)
		{
			_knightDirection = KNIGHTDIRECTION_RIGHT_FIRE;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightFire");
			_knightMotion->start();
		}
	}

	switch (_knightDirection)
	{
	case KNIGHTDIRECTION_RIGHT_STOP: case KNIGHTDIRECTION_LEFT_STOP:
		break;

	case KNIGHTDIRECTION_RIGHT_MOVE: case KNIGHTDIRECTION_RIGHT_MOVE_JUMP:
		_x += SPEED;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;

	case KNIGHTDIRECTION_LEFT_MOVE: case KNIGHTDIRECTION_LEFT_MOVE_JUMP:
		_x -= SPEED;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	}

	_jump->update();
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	KEYANIMANAGER->update();

}

void knight::render(void)
{
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _knightMotion);
}

//Äİ¹é					this
void knight::rightFire(void* obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_RIGHT_STOP);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightRightStop"));
	k->getKnightMotion()->start();
}

void knight::leftFire(void* obj)
{

}

void knight::rightSitFire(void* obj)
{

}

void knight::leftSitFire(void* obj)
{

}

void knight::rightJump(void* obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_RIGHT_STOP);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightRightStop"));
	k->getKnightMotion()->start();
}

void knight::leftJump(void* obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_LEFT_STOP);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightLeftStop"));
	k->getKnightMotion()->start();
}

void knight::rightMoveJump(void* obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_RIGHT_MOVE);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightRightMove"));
	k->getKnightMotion()->start();
}

void knight::leftMoveJump(void* obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_LEFT_MOVE);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightLeftMove"));
	k->getKnightMotion()->start();
}
