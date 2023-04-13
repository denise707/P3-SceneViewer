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

private:
	int ID;
	std::vector<GameObject*> sceneObjectList;
	std::vector<const wchar_t*> modelFileNames;
	IETSemaphore* mutex;
	bool isLoaded = true;
	int loadingPercentage = 0;
	int totalModelCount = 4;
	std::vector <ModelInfo> modelList;
	std::vector <ModelLoaderThread*> threadList;
};

