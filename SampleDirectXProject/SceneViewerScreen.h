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
	const char* currSceneTitle;
	void UpdateScreen();
};

