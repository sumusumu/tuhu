#pragma once
#include "singletonBase.h"
#include <map>

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode* _currentScene;	//현재씬
	static gameNode* _loadingScene;	//로딩씬
	static gameNode* _readyScene;	//교체대기씬

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadThreadID;

public:
	sceneManager();
	~sceneManager();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//씬 추가
	gameNode* addScene(string sceneName, gameNode* scene);

	//로딩씬 추가
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	//씬 체인지
	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, string loadingSceneName);

	//로딩 쓰레드를 위한 함수
	friend DWORD CALLBACK loadingThread(LPVOID prc);
};

