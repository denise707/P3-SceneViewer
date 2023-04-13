#pragma once
#include "UIScreen.h"

class SceneViewerScreen : public UIScreen
{
public:
	SceneViewerScreen();
	~SceneViewerScreen();
	void DrawUI() override;

private:
	float* percentage0;
	float* percentage1;
	float* percentage2;
	float* percentage3;
	float* percentage4;

	const char* currSceneTitle;
	void UpdateScreen();
	void UpdateLoadedCount();
	void UpdateTotalCount();
	void ResetViewAll();

	int loadedCount = 0;
	int totalCount = 0;

	bool isUpdated = false;
	bool modified = false;
};

