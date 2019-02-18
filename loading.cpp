#include "stdafx.h"
#include "loading.h"

loadItem::loadItem(){}
loadItem::~loadItem(){}

HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	_kind = LOADING_KIND_IMAGE_00;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, int x, int y, int width, int height, bool trans, COLORREF transColor)
{
	_kind = LOADING_KIND_IMAGE_01;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, int width, int height, bool trans, COLORREF transColor)
{
	_kind = LOADING_KIND_IMAGE_02;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}
HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	_kind = LOADING_KIND_FRAMEIMAGE_00;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;
	return S_OK;
}
HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{

	_kind = LOADING_KIND_FRAMEIMAGE_01;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}




loading::loading()
{
}


loading::~loading()
{
}

HRESULT loading::init()
{
	//백그라운드 이미지
	_background = IMAGEMANAGER->addImage("bgLoading", "LeagueOfLegend.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_loadingBar = new progressBar;
	_loadingBar->init("loadingBarTop", "loadingBarBottom", WINSIZEX / 2, 650, WINSIZEX, 30);
	_loadingBar->setGauge(0, 0);

	_current = 0;
	
	return S_OK;
}


void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, int x, int y, int width, int height, bool trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, x, y,width, height, trans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, int width, int height, bool trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, trans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, x, y, width, height, frameX, frameY, trans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, frameX, frameY, trans, transColor);
	_vLoadItem.push_back(item);
}

void loading::release()
{

}

void loading::update()
{
	_loadingBar->update();
}

void loading::render()
{
	_background->render(getMemDC());
	_loadingBar->render();
}



//로딩이 되는 중이면 true, 다되면 false
BOOL loading::loadNext()
{
	//현재 아이템 갯수가 벡터 사이즈 이상 넘어가면 -> 로딩이 끝났다
	if (_current >= _vLoadItem.size())
	{
		return false;
	}

	//로딩중
	loadItem* item = _vLoadItem[_current];

	switch (item->getLoadingKind())
	{
		case LOADING_KIND_IMAGE_00:
		{
			tagImageResource imageResource = item->getImageResource();
			IMAGEMANAGER->addImage(imageResource.keyName, imageResource.width, imageResource.height);
		}
		break;
		case LOADING_KIND_IMAGE_01:
		{
			tagImageResource imageResource = item->getImageResource();
			IMAGEMANAGER->addImage(imageResource.keyName, imageResource.fileName,
				imageResource.x, imageResource.y,
				imageResource.width, imageResource.height,
				imageResource.trans, imageResource.transColor);
		}
		break;
		case LOADING_KIND_IMAGE_02:
		{
			tagImageResource imageResource = item->getImageResource();
			IMAGEMANAGER->addImage(imageResource.keyName, imageResource.fileName,
				imageResource.width, imageResource.height,
				imageResource.trans, imageResource.transColor);
		}
		break;
		case LOADING_KIND_FRAMEIMAGE_00:
		{
			tagImageResource imageResource = item->getImageResource();
			IMAGEMANAGER->addFrameImage(imageResource.keyName, imageResource.fileName,
				imageResource.x, imageResource.y,
				imageResource.width, imageResource.height,
				imageResource.frameX, imageResource.frameY,
				imageResource.trans, imageResource.transColor);
		}
		break;
		case LOADING_KIND_FRAMEIMAGE_01:
		{
			tagImageResource imageResource = item->getImageResource();
			IMAGEMANAGER->addFrameImage(imageResource.keyName, imageResource.fileName,
				imageResource.width, imageResource.height,
				imageResource.frameX, imageResource.frameY,
				imageResource.trans, imageResource.transColor);
		}
		break;
		case LOADING_KIND_SOUND_00:
		{

		}
		break;
	}

	//로딩바 이미지 변경
	_loadingBar->setGauge(_current, _vLoadItem.size());

	//카운트 == 로딩률
	_current++;

	return true;
}
