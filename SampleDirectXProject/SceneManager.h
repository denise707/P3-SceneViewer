#pragma once
#include <vector>
#include "Scene.h"
#include "IETSemaphore.h"
#include "SimpleMath.h"

using namespace DirectX;

struct ModelInfo {
	std::string name;
	const wchar_t* fileDir;
	SimpleMath::Vector3 position;
};

class SceneManager
{
private:
	static SceneManager* instance;

public:
	SceneManager();
	~SceneManager();
	static void Initialize(std::vector<IETSemaphore*> mutexList);
	static SceneManager* Get();
	void AddScene(Scene* scene);
	int GetSceneCount();
	Scene* GetScene(int index);
	void UnloadScene(int ID);
	static std::vector<GameObject*>* emptyObjectList;
	static std::vector<GameObject*>* combinedObjectList;
	int currentSceneNum = -1;
	void Update();
	int allLoadedCount = 0;
	int allTotalCount = 0;

private:
	void InitializeUsableModels();
	std::vector<Scene*> sceneList;
	std::vector<IETSemaphore*> mutexList;
	std::vector <ModelInfo> usableModels;
};

