//������ ��� ������Ʈ�� �ٰ��� �Ǵ� �͵��� ����
#pragma once
//===============================================================
// - 2015. 06. 30 - ## ��� ���� ##
//===============================================================

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
//MFC�� �ƴ� ���� ���α׷��� ��쿡��
//WIN32_LEAN_AND_MEAN�� �����ؼ� �ð��� ��������ش�
//(�ʿ���� ��������� ��Ŭ��� �ϴ°� �������ش�)

#include <windows.h>	//������ ��Ŭ��� �������

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <iostream>	//����� ��� ��Ŭ���
#include <tchar.h>	//�⺻������ �����ڵ� �� ���� 2����Ʈ ó��
//WBCS : �����ڵ�
//MBCS : ��Ƽ����Ʈ

#include "randomFunction.h"
#include "commonMacroFunction.h"
#include "utils.h"
#include "keyManager.h"
#include "imageManager.h"
#include "timeManager.h"
#include "effectManager.h"
#include "sceneManager.h"
#include "soundManager.h"
#include "keyAniManager.h"
#include "txtData.h"
#include "database.h"

using namespace std;
using namespace SIERRA_UTIL;

//===========================================
// - 2015.06.30 ## �����ι� ���� ##
//===========================================
#define WINNAME (LPTSTR)(TEXT("WinMain"))

//#define FULLSCREEN

#ifdef FULLSCREEN
#define WINSTARTX 0
#define WINSTARTY 0
#define WINSIZEX GetSystemMetrics(SM_CXSCREEN)
#define WINSIZEY GetSystemMetrics(SM_CYSCREEN)
#else
#define WINSTARTX 50
#define WINSTARTY 100
#define WINSIZEX 800
#define WINSIZEY 800

#endif

#define WINSTYLE WS_CAPTION | WS_SYSMENU

//==========================================
// - 2015.06.30 ## ��ũ�� �Ծ� ##
//==========================================

#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[](p); (p) = NULL;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->Release(); (p) = NULL;}}

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define KEYANIMANAGER keyAniManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define DATABASE database::getSingleton()
//==========================================
// - 2015.06.30 ## ���� ���� ##
//==========================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;

extern BOOL _leftButtonDown;
extern BOOL _rightButtonDown;