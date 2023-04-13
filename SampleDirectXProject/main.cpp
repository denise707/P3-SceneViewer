#include "AppWindow.h"
#include <iostream>

#include "CameraManager.h"
#include "IETSemaphore.h"
#include <vector>

int main()
{
	std::vector <IETSemaphore*> mutexList;

	IETSemaphore scene1_mutex = (1, 1);
	mutexList.push_back(&scene1_mutex);

	IETSemaphore scene2_mutex = (1, 1);
	mutexList.push_back(&scene2_mutex);

	IETSemaphore scene3_mutex = (1, 1);
	mutexList.push_back(&scene3_mutex);

	IETSemaphore scene4_mutex = (1, 1);
	mutexList.push_back(&scene4_mutex);

	IETSemaphore scene5_mutex = (1, 1);
	mutexList.push_back(&scene5_mutex);

	AppWindow::Initialize(mutexList);

	CameraManager::Initialize();
	AppWindow* window = AppWindow::Get();

	if (window->init())
	{
		while (window->IsRunning())
		{
			window->broadcast();
		}
	}

	return 0;
}
