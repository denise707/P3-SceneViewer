#pragma once
#include <vector>
#include "IETSemaphore.h"
#include "GameObject.h"
#include "IExecutionEvent.h"
#include "ModelLoaderThread.h"

struct ModelInfo;

class Scene	: public IExecutionEvent
{
public:
	Scene(int ID, IETSemaphore* mutex, std::vector <ModelInfo> models);
	~Scene();
	void OnStart();
	void OnFinishedExecution() override;
	float GetLoadingPercentage();
	std::vector<GameObject*>* GetObjectList();
	bool isLoaded = true;
	void Update();

private:
	int ID;
	std::vector<GameObject*> sceneObjectList;
	std::vector<const wchar_t*> modelFileNames;
	IETSemaphore* mutex;
	int loadingPercentage = 0;
	int totalModelCount = 4;
	std::vector <ModelInfo> modelList;
	std::vector <ModelLoaderThread*> threadList;
};

