//앞으로 모든 프로젝트의 근간이 되는 것들의 모임
#pragma once
//===============================================================
// - 2015. 06. 30 - ## 헤더 파일 ##
//===============================================================

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
//MFC가 아닌 으용 프로그램의 경우에는
//WIN32_LEAN_AND_MEAN을 정의해서 시간을 단축시켜준다
//(필요없는 헤더파일을 인클루드 하는걸 방지해준다)

#include <windows.h>	//윈도우 인클루드 헤더파일

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <iostream>	//입출력 담당 인클루드
#include <tchar.h>	//기본적으로 유니코드 및 영어 2바이트 처리
//WBCS : 유니코드
//MBCS : 멀티바이트

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
// - 2015.06.30 ## 디파인문 선언 ##
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
// - 2015.06.30 ## 매크로 함쑤 ##
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
// - 2015.06.30 ## 전역 변수 ##
//==========================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;

extern BOOL _leftButtonDown;
extern BOOL _rightButtonDown;