#pragma once
#include "singletonBase.h"
#include <map>

//fmod.hpp 추가
#include "inc/fmod.hpp"

//lib링크
#pragma comment (lib, "lib/fmodex_vc.lib")

//채널 버퍼
#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 10

//총 사운드 버퍼 15개
#define TOTALSOUNDBUFFER EXTRACHANNELBUFFER + SOUNDBUFFER

using namespace FMOD;

class soundManager : public singletonBase<soundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;

private:
	System* _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;
	
public:
	HRESULT init();
	void release();
	void update();

	void addSound(string keyName, string SoundName, bool bgm, bool loop);
	void play(string keyName, float volume = 1.0f); //0.0 ~ 1.0
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	//재생중인즤?
	bool isPlaySound(string keyName);

	//일시정지중인즤?
	bool isPauseSound(string keyName);


	soundManager();
	~soundManager();
};

