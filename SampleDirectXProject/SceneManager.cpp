#include "SceneManager.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	instance = new SceneManager();
}

SceneManager* SceneManager::Get()
{
	return instance;
}

void SceneManager::Update()
{
}

void SceneManager::AddScene(Scene* scene)
{
	this->instance->sceneList.push_back(scene);
}

Scene* SceneManager::GetScene(int index)
{
	return this->sceneList[index];
}
