#pragma once
#include "IETThread.h"
#include "IETSemaphore.h"
#include <vector>
#include "GameObject.h"
#include "IExecutionEvent.h"

class ModelLoaderThread : public IETThread
{
public:
	ModelLoaderThread(const wchar_t* fileDir, std::string name, IETSemaphore* mutex, std::vector<GameObject*>* gameObjectList, IExecutionEvent* execEvent);
	~ModelLoaderThread();
	bool isRunning;
	void destroy();

private:
	void run() override;
	const wchar_t* fileDir;
	std::vector<GameObject*>* gameObjectList;
	std::string name;
	IETSemaphore* mutex;
	IExecutionEvent* execEvent;
};

