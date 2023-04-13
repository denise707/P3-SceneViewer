#include "Scene.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include "GraphicsEngine.h"

Scene::Scene(int ID, IETSemaphore* mutex, std::vector <ModelInfo> models)
{
	this->ID = ID;
	this->mutex = mutex;
	this->modelList = models;
}

Scene::~Scene()
{
}

void Scene::OnStart()
{
	for (int i = 0; i < totalModelCount; i++) {
		ModelLoaderThread* modelLoaderThread = new ModelLoaderThread(modelList[i].fileDir, modelList[i].name, mutex, &sceneObjectList, this);
		threadList.push_back(modelLoaderThread);
		modelLoaderThread->start();	
	}
}

void Scene::OnFinishedExecution()
{
	this->loadingPercentage++;
}

float Scene::GetLoadingPercentage()
{
	return (float)this->loadingPercentage / this->totalModelCount;
}

std::vector<GameObject*>* Scene::GetObjectList()
{
	return &this->sceneObjectList;
}

void Scene::Update()
{
	if (!isLoaded) {
		for (int i = 0; i < threadList.size(); i++) {
			std::cout << i << std::endl;
			if (threadList[i] != NULL) {
				threadList[i]->isRunning = false;
				//threadList[i]->destroy();
			}
				
		}
		this->loadingPercentage = 0;
		//GraphicsEngine::get()->getMeshManager()->deleteMesh();
		isLoaded = true;
	}
}

