#include "Scene.h"
#include "ModelLoaderThread.h"
#include "GameObjectManager.h"

Scene::Scene(IETSemaphore* mutex)
{
	this->mutex = mutex;
}

Scene::~Scene()
{
}

void Scene::OnStart()
{
	if (id == 0) {
		modelFileNames.push_back(L"Assets\\Meshes\\armadillo.obj");
		modelFileNames.push_back(L"Assets\\Meshes\\teapot.obj");
		modelFileNames.push_back(L"Assets\\Meshes\\bunny.obj");
		modelFileNames.push_back(L"Assets\\Meshes\\statue.obj");
	}

	if (id == 1) {
		modelFileNames.push_back(L"Assets\\Meshes\\asteroid.obj");
		modelFileNames.push_back(L"Assets\\Meshes\\monitor.obj");
		modelFileNames.push_back(L"Assets\\Meshes\\spaceship.obj");
		modelFileNames.push_back(L"Assets\\Meshes\\sponza_basic.obj");
	}
	
	this->totalModelCount = modelFileNames.size();

	std::string temp;

	for (int i = 0; i < modelFileNames.size(); i++) {
		if (id == 0) {
			switch (i)
			{
			case 0: temp = "1"; break;
			case 1: temp = "2"; break;
			case 2: temp = "3"; break;
			case 3: temp = "4"; break;
			}
		}
		

		if (id == 1) {
			switch (i)
			{
			case 0: temp = "5"; break;
			case 1: temp = "6"; break;
			case 2: temp = "7"; break;
			case 3: temp = "8"; break;
			}
		}
		
		ModelLoaderThread* modelLoaderThread = new ModelLoaderThread(modelFileNames[i], temp, mutex, &sceneObjectList, this);
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
