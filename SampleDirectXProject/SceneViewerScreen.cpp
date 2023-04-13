#include "SceneViewerScreen.h"
#include "SceneManager.h"
#include "GameObjectManager.h"

SceneViewerScreen::SceneViewerScreen(): UIScreen("SceneViewerScreen", true)
{
	percentage = new float();
}

SceneViewerScreen::~SceneViewerScreen()
{
}

void SceneViewerScreen::DrawUI()
{
	UpdateScreen();
	ImGui::Begin("Scene Viewer", &isActive);

	//Scene 1
	*percentage = SceneManager::Get()->GetScene(0)->GetLoadingPercentage();
	ImGui::Text("Scene 1\n");
	ImGui::SliderFloat("##Percentage1", percentage, 0, 1);
	if (ImGui::Button("Scene 1", ImVec2(150, 20))) { 
		currentScene = 0; 
	}
	if (ImGui::Button("Load Scene 1", ImVec2(150, 20))) {
		SceneManager::Get()->GetScene(0)->isLoaded = true;
		SceneManager::Get()->GetScene(0)->OnStart();
	}
	if (ImGui::Button("Unload Scene 1", ImVec2(150, 20))) { 
		SceneManager::Get()->UnloadScene(0);
		SceneManager::Get()->GetScene(0)->isLoaded = false;
		SceneManager::Get()->GetScene(0)->Update();
	}

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	//Scene 2
	*percentage = SceneManager::Get()->GetScene(1)->GetLoadingPercentage();
	ImGui::Text("Scene 2\n");
	ImGui::SliderFloat("##Percentage2", percentage, 0, 1);
	if (ImGui::Button("Scene 2", ImVec2(150, 20))) { currentScene = 1; }
	if (ImGui::Button("Unload Scene 2", ImVec2(150, 20))) { }
	
	ImGui::End();
}

void SceneViewerScreen::UpdateScreen()
{
	GameObjectManager::Get()->ChangeObjectList(SceneManager::Get()->GetScene(currentScene)->GetObjectList());
}
