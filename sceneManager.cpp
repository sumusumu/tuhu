#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

//�ε� �����带 ���� �Լ�
DWORD CALLBACK loadingThread(LPVOID prc)
{
	//��ü�� init �Լ��� �����Ѵ�
	sceneManager::_readyScene->init();

	//���� ���� ��ü�� ������ �ٲ۴�
	sceneManager::_currentScene = sceneManager::_readyScene;

	//�ε����� ���� �Ѵ�
	sceneManager::_loadingScene->release();
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	return 0;

}

gameNode* sceneManager::_currentScene = NULL;
gameNode* sceneManager::_loadingScene = NULL;
gameNode* sceneManager::_readyScene = NULL;

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}

HRESULT sceneManager::init(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;

	return S_OK;
}

void sceneManager::release(void)
{
	//�� ��ü�� ���鼭 �����ش�(����)
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		//�������� �ݺ��ڸ� ������Ű�� �ʴ´�
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);

		}
		else
		{
			++miSceneList;
		}
	}

	_mSceneList.clear();
}

void sceneManager::update(void)
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render(void)
{
	if (_currentScene) _currentScene->render();
}

//�� �߰�
gameNode* sceneManager::addScene(string sceneName, gameNode* scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

//�ε��� �߰�
gameNode* sceneManager::addLoadingScene(string loadingSceneName, gameNode* scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

//�� ü����
HRESULT sceneManager::changeScene(string sceneName)
{
	//�ٲٷ��ϴ� ���� ã�´�
	mapSceneIter find = _mSceneList.find(sceneName);

	//�ٲ��� ���ϸ� false
	if (find == _mSceneList.end()) return E_FAIL;

	//�ٲٸ� ������
	if (find->second == _currentScene) return S_OK;

	//����Ǵ� ���� �ʱ�ȭ ���ش�
	if (SUCCEEDED(find->second->init()))
	{
		//������ ���� ������ �� ���� �������ش�
		if (_currentScene) _currentScene->release();
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT sceneManager::changeScene(string sceneName, string loadingSceneName)
{
	//�ٲٷ��ϴ� ���� ã�´�
	mapSceneIter find = _mSceneList.find(sceneName);

	//�ٲ��� ���ϸ� false
	if (find == _mSceneList.end()) return E_FAIL;

	//�ٲٸ� ������
	if (find->second == _currentScene) return S_OK;

	//�ٲٷ� �ϴ� ���� ã�´�
	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	
	//����Ǵ� ���� �ʱ�ȭ ���ش�
	if (SUCCEEDED(find->second->init()))
	{
		//������ ���� ������ �� ���� �������ش�
		if (_currentScene) _currentScene->release();

		//�ٲ�� �� �ε��� ������
		_loadingScene = findLoading->second;

		//�ε� ���� �� ���� �� �� ����
		_readyScene = find->second;

		//�ε��� �������Ƿ� (������ ȣ�����ش�)
		CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &_loadThreadID));

	}

	return E_FAIL;
}
