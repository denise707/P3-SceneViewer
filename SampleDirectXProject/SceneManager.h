#pragma once
#include <vector>
#include "Scene.h"
#include "IETSemaphore.h"

struct ModelInfo {
	std::string name;
	const wchar_t* fileDir;
};

class SceneManager
{
private:
	static SceneManager* instance;

public:
	SceneManager();
	~SceneManager();
	static void Initialize(IETSemaphore* mutex);
	static SceneManager* Get();
	void AddScene(Scene* scene);
	Scene* GetScene(int index);
	void UnloadScene(int ID);

private:
	void InitializeUsableModels();
	std::vector<Scene*> sceneList;
	Scene* currentScene;
	IETSemaphore* mutex;
	std::vector <ModelInfo> usableModels;
};

