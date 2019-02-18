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
	static gameNode* _currentScene;	//�����
	static gameNode* _loadingScene;	//�ε���
	static gameNode* _readyScene;	//��ü����

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

	//�� �߰�
	gameNode* addScene(string sceneName, gameNode* scene);

	//�ε��� �߰�
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	//�� ü����
	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, string loadingSceneName);

	//�ε� �����带 ���� �Լ�
	friend DWORD CALLBACK loadingThread(LPVOID prc);
};

