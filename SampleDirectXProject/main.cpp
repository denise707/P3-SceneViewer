#include "AppWindow.h"
#include <iostream>

#include "CameraManager.h"
#include "IETSemaphore.h"

int main()
{
	IETSemaphore mutex = (1, 1);

	AppWindow::Initialize(&mutex);
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
