#pragma once
#include <vector>
#include "Scene.h"

class SceneManager
{
private:
	static SceneManager* instance;

public:
	SceneManager();
	~SceneManager();
	static void Initialize();
	static SceneManager* Get();
	void Update();
	void AddScene(Scene* scene);
	Scene* GetScene(int index);

private:
	std::vector<Scene*> sceneList;
	Scene* currentScene;
};

