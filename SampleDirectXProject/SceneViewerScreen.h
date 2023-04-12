#pragma once
#include "UIScreen.h"

class SceneViewerScreen : public UIScreen
{
public:
	SceneViewerScreen();
	~SceneViewerScreen();
	void DrawUI() override;

private:
	float* percentage;
	int currentScene = 0;
	void UpdateScreen();
};

