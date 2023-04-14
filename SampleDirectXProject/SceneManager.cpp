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

	//Scene 3
	for (int i = 8; i < 12; i++) {
		tempList.push_back(instance->usableModels[i]);
	}
	Scene* scene3 = new Scene(2, mutexList[2], tempList);
	SceneManager::Get()->AddScene(scene3);

	tempList.clear();

	//Scene 4
	for (int i = 12; i < 16; i++) {
		tempList.push_back(instance->usableModels[i]);
	}
	Scene* scene4 = new Scene(3, mutexList[3], tempList);
	SceneManager::Get()->AddScene(scene4);

	tempList.clear();

	//Scene 5 is a mix of objects from Scene 1 - 4
	for (int i = 0; i < 16; i += 4 ) {
		std::cout << "Model: " << i << std::endl;
		tempList.push_back(instance->usableModels[i]);
	}
	Scene* scene5 = new Scene(4, mutexList[4], tempList);
	SceneManager::Get()->AddScene(scene5);

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
#pragma region FirstGroup
	ModelInfo model0 = { "Armadillo", L"Assets\\Meshes\\armadillo.obj" };//large file
	usableModels.push_back(model0);

	ModelInfo model1 = { "Teapot", L"Assets\\Meshes\\teapot.obj" };
	usableModels.push_back(model1);

	ModelInfo model2= { "Sword", L"Assets\\Meshes\\Sword.obj" };
	usableModels.push_back(model2);

	ModelInfo model3 = { "Statue", L"Assets\\Meshes\\statue.obj" };
	usableModels.push_back(model3);
#pragma endregion

#pragma region SecondGroup

	ModelInfo model4 = { "Monitor", L"Assets\\Meshes\\monitor.obj" };
	usableModels.push_back(model4);

	ModelInfo model5 = { "Lion", L"Assets\\Meshes\\lion.obj" }; // large file
	usableModels.push_back(model5);

	ModelInfo model6 = { "LV", L"Assets\\Meshes\\lv.obj" };
	usableModels.push_back(model6);

	ModelInfo model7 = { "Spaceship", L"Assets\\Meshes\\spaceship.obj" };
	usableModels.push_back(model7);

#pragma endregion

#pragma region ThirdGroup

	ModelInfo model8 = { "Asteroid", L"Assets\\Meshes\\asteroid.obj" };
	usableModels.push_back(model8);

	ModelInfo model9 = { "Chair", L"Assets\\Meshes\\chair.obj" };// large file
	usableModels.push_back(model9);

	ModelInfo model10 = { "Bunny", L"Assets\\Meshes\\bunny.obj" };
	usableModels.push_back(model10);

	ModelInfo model11 = { "Dango", L"Assets\\Meshes\\dango.obj" };
	usableModels.push_back(model11);

#pragma endregion

#pragma region FourthGroup

	ModelInfo model12 = { "Flamingo", L"Assets\\Meshes\\flamingo.obj" };
	usableModels.push_back(model12);

	ModelInfo model13 = { "Ganesha", L"Assets\\Meshes\\ganesha.obj" };// large file
	usableModels.push_back(model13);

	ModelInfo model14 = { "Amongus", L"Assets\\Meshes\\amongus.obj" };
	usableModels.push_back(model14);

	ModelInfo model15 = { "Hat", L"Assets\\Meshes\\hat.obj" };
	usableModels.push_back(model15);

#pragma endregion
}
