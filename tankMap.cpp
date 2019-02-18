#include "stdafx.h"
#include "tankMap.h"


tankMap::tankMap()
{
}


tankMap::~tankMap()
{
}

HRESULT tankMap::init(void)
{
	IMAGEMANAGER->addFrameImage("mapTiles", "maptiles.bmp", 0, 0, 640, 288, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	//맵을 불러온다
	load();

	return S_OK;
}

void tankMap::release(void)
{

}

void tankMap::update(void)
{

}

void tankMap::render(void)
{
	IMAGEMANAGER->render("mapTiles", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth(), 0);

	//지형 뿌려준다
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->frameRender("mapTiles", getMemDC(), _tiles[i].rc.left,
			_tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}

	//오브젝트 뿌림뿌림
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_NONE) continue;
		IMAGEMANAGER->frameRender("mapTiles", getMemDC(), _tiles[i].rc.left,
			_tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
	}

}

//맵 로드
void tankMap::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile("map1.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);
	CloseHandle(file);

	//오브젝트 및 속성을 정의한다
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_TANK1 || _tiles[i].obj == OBJ_TANK2)
		{
			_tiles[i].obj = OBJ_NONE;
		}
	}

	memset(_attribute, 0, sizeof(DWORD) * TILEX * TILEY);
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].terrain == TR_WATER) _attribute[i] |= ATTR_UNMOVAL;
		if (_tiles[i].obj == OBJ_BLOCK1) _attribute[i] |= ATTR_UNMOVAL;
		if (_tiles[i].obj == OBJ_BLOCK3) _attribute[i] |= ATTR_UNMOVAL;
		if (_tiles[i].obj == OBJ_BLOCKS) _attribute[i] |= ATTR_UNMOVAL;
	}

}