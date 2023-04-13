#include "LoadingScreen.h"
#include "SceneManager.h"

LoadingScreen::LoadingScreen() : UIScreen("LoadingScreen", true)
{
	percentage = new float();
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::DrawUI()
{
	if (SceneManager::Get()->currentSceneNum != -1) {
		*percentage = SceneManager::Get()->GetScene(SceneManager::Get()->currentSceneNum)->GetLoadingPercentage();

		if (*percentage < 100) {
			ImGui::Begin("Loading", &isActive, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
			ImGui::SliderFloat("##Percentage1", percentage, 0, 100);
			ImGui::End();
		}
	}
}
