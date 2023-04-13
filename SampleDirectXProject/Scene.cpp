#include "Scene.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include "GraphicsEngine.h"
#include <random>

Scene::Scene(int ID, IETSemaphore* mutex, std::vector <ModelInfo> models)
{
	this->ID = ID;
	this->mutex = mutex;
	this->modelList = models;

	for (int i = 0; i < models.size(); i++) {

		//Randomize Position
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> distr(0, 2.5f); // define the range

		SimpleMath::Vector3 position = { (float)distr(gen), 0, (float)distr(gen) };
		modelList[i].position = position;
	}

	totalModelCount = modelList.size();
}

Scene::~Scene()
{
}

void Scene::OnStart()
{
	isLoaded = true;

	for (int i = 0; i < modelList.size(); i++) {
		ModelLoaderThread* modelLoaderThread = new ModelLoaderThread(modelList[i].fileDir, modelList[i].name, mutex, &sceneObjectList, this, modelList[i].position);
		threadList.push_back(modelLoaderThread);
		modelLoaderThread->start();	
	}
}

void Scene::OnFinishedExecution()
{
	this->loadingPercentage++;

	if (this->loadingPercentage == totalModelCount) {
		isFinished = true;
	}
}

float Scene::GetLoadingPercentage()
{
	return (float)this->loadingPercentage / this->modelList.size() * 100;
}

std::vector<GameObject*>* Scene::GetObjectList()
{
	return &this->sceneObjectList;
}

void Scene::Unload()
{
	for (int i = 0; i < threadList.size(); i++) {
		threadList[i]->isRunning = false;
	}
	this->loadingPercentage = 0;

	this->sceneObjectList.clear();
	this->isLoaded = false;
}

bool Scene::IsLoaded()
{
	return this->isLoaded;
}

float Scene::GetLoadedCount()
{
	return this->loadingPercentage;
}

int Scene::GetTotalCount()
{
	return totalModelCount;
}

