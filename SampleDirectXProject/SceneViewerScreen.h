#pragma once
#include "UIScreen.h"

struct Image {
	int my_image_width = 0;
	int my_image_height = 0;
	ID3D11ShaderResourceView* my_texture = NULL;
};

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
	std::string fpsText;

	void UpdateScreen();
	void UpdateLoadedCount();
	void UpdateTotalCount();
	void ResetViewAll();
	void CalculateFPS();
	void Spacing();

	int loadedCount = 0;
	int totalCount = 0;

	bool isUpdated = false;
	
	float ticks = 0.0f;

	std::vector <Image> imageList;
};

