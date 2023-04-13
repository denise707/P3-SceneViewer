#include "SceneManager.h"
#include "GameObjectManager.h"

SceneManager* SceneManager::instance = nullptr;
std::vector<GameObject*>* SceneManager::emptyObjectList = new std::vector<GameObject*>();
std::vector<GameObject*>* SceneManager::combinedObjectList = new std::vector<GameObject*>();

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize(std::vector<IETSemaphore*> mutexList)
{
	instance = new SceneManager();
	instance->mutexList = mutexList;

	std::vector <ModelInfo> tempList;

	//Initialize scenes
	instance->InitializeUsableModels();

	//Scene 1
	for (int i = 0; i < 4; i++) {
		tempList.push_back(instance->usableModels[i]);
	}
	Scene* scene1 = new Scene(0, mutexList[0], tempList);
	SceneManager::Get()->AddScene(scene1);

	tempList.clear();

	//Scene 2
	for (int i = 4; i < 8; i++) {
		tempList.push_back(instance->usableModels[i]);
	}
	Scene* scene2 = new Scene(1, mutexList[1], tempList);
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

int SceneManager::GetSceneCount()
{
	return sceneList.size();
}

Scene* SceneManager::GetScene(int index)
{
	return this->sceneList[index];
}

void SceneManager::UnloadScene(int ID)
{
	instance->sceneList[ID]->Unload();
}

void SceneManager::Update()
{
	bool isDone = true;
	for (int i = 0; i < sceneList.size(); i++) {
		if (!instance->sceneList[i]->isFinished)
			isDone = false;
	}

	if (isDone) {
		for (int i = 0; i < instance->sceneList.size(); i++) {
			for (int j = 0; j < instance->sceneList[i]->GetObjectList()->size(); j++) {
				GameObject* obj = instance->sceneList[i]->GetObjectList()->at(j);
				combinedObjectList->push_back(obj);
			}
		}
	}
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
