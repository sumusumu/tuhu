#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager()
	: _system(NULL),
	_sound(NULL),
	_channel(NULL)
{
}


soundManager::~soundManager()
{
}

HRESULT soundManager::init()
{
	//사운드 시스템 생성
	System_Create(&_system);

	//채널수 설정
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//사운드, 채널, 동적할당(필수)
	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	//스택메모리 밀어준다
	memset(_sound, 0, sizeof(Sound*)* (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));
	

	return S_OK;
}

void soundManager::release()
{

}

void soundManager::update()
{

}

void soundManager::addSound(string keyName, string SoundName, bool bgm, bool loop)
{
	//루프 여부
	if (loop)
	{
		if (bgm)
		{
			_system->createStream(SoundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(SoundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		_system->createStream(SoundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	//맵에 사운드를 키값과 함께 넣어줌
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

void soundManager::play(string keyName, float volume) //0.0 ~ 1.0
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 플레이 해줌
			_system->playSound(FMOD_CHANNEL_FREE, _sound[count], false, &_channel[count]);

			//볼륨 셋팅
			_channel[count]->setVolume(volume);
			break;
		}
	}
}

void soundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void soundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}


//재생중인즤?
bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}


//일시정지중인즤?
bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}
