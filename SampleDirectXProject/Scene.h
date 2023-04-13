#pragma once
#include <vector>
#include "IETSemaphore.h"
#include "GameObject.h"
#include "IExecutionEvent.h"
#include "ModelLoaderThread.h"
#include "SimpleMath.h"

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
	void Unload();
	bool IsLoaded();
	float GetLoadedCount();
	int GetTotalCount();
	bool isFinished = false;

private:
	int ID;
	std::vector<GameObject*> sceneObjectList;
	std::vector<const wchar_t*> modelFileNames;
	IETSemaphore* mutex;
	bool isLoaded = true;
	int totalModelCount = 0;
	int loadingPercentage = 0;
	std::vector <ModelInfo> modelList;
	std::vector <ModelLoaderThread*> threadList;
};

