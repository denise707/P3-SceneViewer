#include "SceneViewerScreen.h"
#include "SceneManager.h"
#include "GameObjectManager.h"

SceneViewerScreen::SceneViewerScreen(): UIScreen("SceneViewerScreen", true)
{
	percentage = new float();
	currSceneTitle = "Viewing: None";
}

SceneViewerScreen::~SceneViewerScreen()
{
}

void SceneViewerScreen::DrawUI()
{
	UpdateScreen();
	ImGui::Begin("Scene Viewer", &isActive, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
	ImGui::Text(currSceneTitle);
	ImGui::PopStyleColor();
	

	//Scene 1
	*percentage = SceneManager::Get()->GetScene(0)->GetLoadingPercentage();
	ImGui::Text("Scene 1\n");
	ImGui::SliderFloat("##Percentage1", percentage, 0, 100);
	if (ImGui::Button("View Scene 1", ImVec2(150, 20))) { 
		SceneManager::Get()->currentSceneNum = 0;
		currSceneTitle = "Viewing: Scene 1";
	}
	if (ImGui::Button("Load Scene 1", ImVec2(150, 20))) {
		if (!SceneManager::Get()->GetScene(0)->IsLoaded()) {
			SceneManager::Get()->GetScene(0)->OnStart();
		}
	}
	if (ImGui::Button("Unload Scene 1", ImVec2(150, 20))) { 
		SceneManager::Get()->UnloadScene(0);
	}

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	//Scene 2
	*percentage = SceneManager::Get()->GetScene(1)->GetLoadingPercentage();
	ImGui::Text("Scene 2\n");
	ImGui::SliderFloat("##Percentage2", percentage, 0, 100);
	if (ImGui::Button("View Scene 2", ImVec2(150, 20))) { 
		SceneManager::Get()->currentSceneNum = 1;
		currSceneTitle = "Viewing: Scene 2";
	}
	if (ImGui::Button("Unload Scene 2", ImVec2(150, 20))) { }
	
	ImGui::End();
}

void SceneViewerScreen::UpdateScreen()
{
	if (SceneManager::Get()->currentSceneNum != -1 && SceneManager::Get()->GetScene(SceneManager::Get()->currentSceneNum)->GetLoadingPercentage() == 100) {
		GameObjectManager::Get()->ChangeObjectList(SceneManager::Get()->GetScene(SceneManager::Get()->currentSceneNum)->GetObjectList());
	}
	
	else {
		GameObjectManager::Get()->ChangeObjectList(SceneManager::Get()->emptyObjectList);
	}
}
