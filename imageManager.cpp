#include "stdafx.h"
#include "imageManager.h"


imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}

HRESULT imageManager::init()
{
	return S_OK;
}

void imageManager::release()
{
	deleteAll();
}

image* imageManager::addImage(string strKey, int width, int height)
{
	//동일한 이미지 있는지 찾는다
	image* img = findImage(strKey);

	//키값과 같은 이미지가 이미 있다면 추가하지 않는다 그리고 기존의 이미지를 반환한다
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되어있지 않다면
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const DWORD resID,
	int width, int height, bool trans, COLORREF transColor)
{
	//동일한 이미지 있는지 찾는다
	image* img = findImage(strKey);

	//키값과 같은 이미지가 이미 있다면 추가하지 않는다 그리고 기존의 이미지를 반환한다
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되어있지 않다면
	if (FAILED(img->init(resID, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char* fileName,
	int width, int height, bool trans, COLORREF transColor)
{
	//동일한 이미지 있는지 찾는다
	image* img = findImage(strKey);

	//키값과 같은 이미지가 이미 있다면 추가하지 않는다 그리고 기존의 이미지를 반환한다
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되어있지 않다면
	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;

}

image* imageManager::addImage(string strKey, const char* fileName,
	float x, float y, int width, int height, bool trans, COLORREF transColor)
{
	//동일한 이미지 있는지 찾는다
	image* img = findImage(strKey);

	//키값과 같은 이미지가 이미 있다면 추가하지 않는다 그리고 기존의 이미지를 반환한다
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되어있지 않다면
	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//프레임 이미지
image* imageManager::addFrameImage(string strKey, const char* fileName, float x, float y,
	int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	//동일한 이미지 있는지 찾는다
	image* img = findImage(strKey);

	//키값과 같은 이미지가 이미 있다면 추가하지 않는다 그리고 기존의 이미지를 반환한다
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되어있지 않다면
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addFrameImage(string strKey, const char* fileName, int width, int height,
	int frameX, int frameY, bool trans, COLORREF transColor)
{
	//동일한 이미지 있는지 찾는다
	image* img = findImage(strKey);

	//키값과 같은 이미지가 이미 있다면 추가하지 않는다 그리고 기존의 이미지를 반환한다
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되어있지 않다면
	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}


//이미지 찾는 함수
image* imageManager::findImage(string strKey)
{
	//해당키가 있는지 여부를 검사한다
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}

//이미지 지운다
BOOL imageManager::deleteImage(string strKey)
{
	//해당 키값 있는지 검색한다
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		key->second->release();

		SAFE_DELETE(key->second);

		_mImageList.erase(key);

		return true;
	}

	return false;
}

BOOL imageManager::deleteAll(void)
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	_mImageList.clear();

	return TRUE;
}

//렌더함수
void imageManager::render(string strKey, HDC hdc)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY,
	int sourX, int sourY, int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void  imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY);
}

void  imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}