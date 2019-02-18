#include "stdafx.h"
#include "timer.h"
#include <mmsystem.h>

//TimeGetTime 함수를 사용하기 위한 라이브러리

//윈도우가 실행중인 시간을 알려주는 API
#pragma comment(lib, "winmm.lib")


timer::timer()
{
}


timer::~timer()
{
}

HRESULT timer::init(void)
{
	//고성능 타이머 지원여부 체크
	//만약 지원이 되면 초당 밀리세컨까지 값이 들어감(1000 == 1초)
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		_timeScale = 1.0f / _periodFrequency;
	}
	else
	{
		_isHardware = false;

		//밀리 세컨드 단위로 초를 강제로 맞춤
		_lastTime = timeGetTime();
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0;
	_worldTime = 0.0f;

	return S_OK;
}

//0.001초 갱신
void timer::tick(float lockFPS)
{
	//고성능 타이머를 지원하늬
	if (_isHardware)
	{
		//초 정밀한 마이크로초 단위로 계산
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		//지원하지 않으면 time 함수 이용
		_curTime = timeGetTime();
	}

	//마지막 시간과 현재시간의 경과량(화면 갱신률)
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	if (lockFPS > 0.0f)
	{
		//고정프레임의 시간을 만족할때까지 뤂
		while (_timeElapsed < (1.0f / lockFPS))
		{
			if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else _curTime = timeGetTime();

			//마지막 시간과 현재시간의 경과량
			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;
	_FPSFrameCount++;
	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;

	//프레임 초기화는 1초마다 해준다
	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}

}

unsigned long timer::getFrameRate(char* str) const
{
	if (str != NULL)
	{
		wsprintf(str, "FPS : %d", _frameRate);
	}

	return _frameRate;

}