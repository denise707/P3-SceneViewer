#include "SceneManager.h"
#include "GameObjectManager.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize(IETSemaphore* mutex)
{
	instance = new SceneManager();
	instance->mutex = mutex;

	std::vector <ModelInfo> tempList;

	//Initialize scenes
	instance->InitializeUsableModels();

	//Scene 1
	for (int i = 0; i < 4; i++) {
		tempList.push_back(instance->usableModels[i]);
	}
	Scene* scene1 = new Scene(0, mutex, tempList);
	SceneManager::Get()->AddScene(scene1);

	tempList.clear();

	//Scene 2
	for (int i = 4; i < 8; i++) {
		tempList.push_back(instance->usableModels[i]);
	}
	Scene* scene2 = new Scene(1, mutex, tempList);
	SceneManager::Get()->AddScene(scene2);

	tempList.clear();
}

SceneManager* SceneManager::Get()
{
	return instance;
}

void SceneManager::AddScene(Scene* scene)
{
	this->instance->sceneList.push_back(scene);
}

Scene* SceneManager::GetScene(int index)
{
	return this->sceneList[index];
}

void SceneManager::UnloadScene(int ID)
{
	instance->sceneList[ID]->GetObjectList()->clear();
}

void SceneManager::InitializeUsableModels()
{
	ModelInfo model0 = { "Armadillo", L"Assets\\Meshes\\armadillo.obj" };
	usableModels.push_back(model0);

	ModelInfo model1 = { "Teapot", L"Assets\\Meshes\\teapot.obj" };
	usableModels.push_back(model1);

	ModelInfo model2 = { "Bunny", L"Assets\\Meshes\\bunny.obj" };
	usableModels.push_back(model2);

	ModelInfo model3 = { "Statue", L"Assets\\Meshes\\statue.obj" };
	usableModels.push_back(model3);

	ModelInfo model4 = { "Asteroid", L"Assets\\Meshes\\asteroid.obj" };
	usableModels.push_back(model4);

	ModelInfo model5 = { "Monitor", L"Assets\\Meshes\\monitor.obj" };
	usableModels.push_back(model5);

	ModelInfo model6 = { "Spaceship", L"Assets\\Meshes\\spaceship.obj" };
	usableModels.push_back(model6);

	ModelInfo model7 = { "Sponza", L"Assets\\Meshes\\sponza_basic.obj" };
	usableModels.push_back(model7);
}
