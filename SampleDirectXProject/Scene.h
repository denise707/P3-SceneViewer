#pragma once
#include <vector>
#include "IETSemaphore.h"
#include "GameObject.h"
#include "IExecutionEvent.h"

class Scene	: public IExecutionEvent
{
public:
	Scene(IETSemaphore* mutex);
	~Scene();
	void OnStart();
	void OnFinishedExecution() override;
	float GetLoadingPercentage();
	int id = 0;
	std::vector<GameObject*>* GetObjectList();

private:
	std::vector<GameObject*> sceneObjectList;
	std::vector<const wchar_t*> modelFileNames;
	IETSemaphore* mutex;
	int loadingPercentage = 0;
	int totalModelCount = 0;
};

