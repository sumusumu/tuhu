#pragma once
#include "singletonBase.h"
#include "image.h"
#include <map>

class imageManager : public singletonBase<imageManager>
{
public:
	typedef map<string, image*> mapImageList;			//이미지 리스트 맵
	typedef map<string, image*>::iterator mapImageIter;	//이미지 리스트 이터레이터

private:
	mapImageList _mImageList;	//맵으로 구현된 이미지 리스트

public:
	HRESULT init();

	void release();

	image* addImage(string strKey, int width, int height);

	image* addImage(string strKey, const DWORD resID,
		int width, int height, bool trans, COLORREF transColor);

	image* addImage(string strKey, const char* fileName,
		int width, int height, bool trans, COLORREF transColor);

	image* addImage(string strKey, const char* fileName, 
		float x, float y, int width, int height, bool trans, COLORREF transColor);

	//프레임 이미지
	image* addFrameImage(string strKey, const char* fileName, float x, float y,
		int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	image* addFrameImage(string strKey, const char* fileName, int width, int height,
		int frameX, int frameY, bool trans, COLORREF transColor);


	//이미지 찾는 함수
	image* findImage(string strKey);

	//이미지 지운다
	BOOL deleteImage(string strKey);

	BOOL deleteAll(void);

	//렌더함수
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY,
		int sourX, int sourY, int sourWidth, int sourHeight);

	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);


	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	
	
	imageManager();
	~imageManager();
};

