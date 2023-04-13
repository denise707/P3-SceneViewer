#include "SceneViewerScreen.h"
#include "SceneManager.h"
#include "GameObjectManager.h"

SceneViewerScreen::SceneViewerScreen(): UIScreen("SceneViewerScreen", true)
{
	percentage0 = new float();
	percentage1 = new float();
	percentage2 = new float();
	percentage3 = new float();
	percentage4 = new float();

	currSceneTitle = "Viewing: None";
}

SceneViewerScreen::~SceneViewerScreen()
{
}

void SceneViewerScreen::DrawUI()
{
	UpdateLoadedCount();
	UpdateTotalCount();
	UpdateScreen();

	ImGui::Begin("Scene Viewer", &isActive, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
	ImGui::Text(currSceneTitle);
	ImGui::PopStyleColor();
	
	ImGui::Spacing();
	ImGui::Spacing();

	//Scene 1
	*percentage0 = SceneManager::Get()->GetScene(0)->GetLoadingPercentage();
	ImGui::Text("Scene 1\n");
	ImGui::SliderFloat("##Percentage1", percentage0, 0, 100);
	if (ImGui::Button("View Scene 1", ImVec2(150, 20))) { 
		SceneManager::Get()->currentSceneNum = 0;
		currSceneTitle = "Viewing: Scene 1";
		ResetViewAll();
	}
	if (ImGui::Button("Load Scene 1", ImVec2(150, 20))) {
		if (!SceneManager::Get()->GetScene(0)->IsLoaded()) {
			SceneManager::Get()->GetScene(0)->OnStart();
			ResetViewAll();
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
	*percentage1 = SceneManager::Get()->GetScene(1)->GetLoadingPercentage();
	ImGui::Text("Scene 2\n");
	ImGui::SliderFloat("##Percentage2", percentage1, 0, 100);
	if (ImGui::Button("View Scene 2", ImVec2(150, 20))) { 
		SceneManager::Get()->currentSceneNum = 1;
		currSceneTitle = "Viewing: Scene 2";
		ResetViewAll();
	}
	if (ImGui::Button("Unload Scene 2", ImVec2(150, 20))) { }
	
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 255, 0, 100));
	if (ImGui::Button("View All", ImVec2(150, 20))) {
		SceneManager::Get()->currentSceneNum = 6;
	}
	ImGui::PopStyleColor();

	ImGui::End();
}

void SceneViewerScreen::UpdateScreen()
{
	if (totalCount != 0 && loadedCount == totalCount && !isUpdated) {
		SceneManager::Get()->Update();
		isUpdated = true;
	}

	if (SceneManager::Get()->currentSceneNum == 6) {
		if(loadedCount != totalCount) { SceneManager::Get()->combinedObjectList->clear(); }
		GameObjectManager::Get()->ChangeObjectList(SceneManager::Get()->combinedObjectList);
	}
	
	else if (SceneManager::Get()->currentSceneNum != -1 && SceneManager::Get()->currentSceneNum != 6 && SceneManager::Get()->GetScene(SceneManager::Get()->currentSceneNum)->GetLoadingPercentage() == 100) {
		GameObjectManager::Get()->ChangeObjectList(SceneManager::Get()->GetScene(SceneManager::Get()->currentSceneNum)->GetObjectList());
	}
	
	else {
		GameObjectManager::Get()->ChangeObjectList(SceneManager::Get()->emptyObjectList);
	}
}

void SceneViewerScreen::UpdateLoadedCount()
{
	int count = 0;
	for (int i = 0; i < SceneManager::Get()->GetSceneCount(); i++) {
		count += SceneManager::Get()->GetScene(i)->GetLoadedCount();
	}
	loadedCount = count;
	SceneManager::Get()->allLoadedCount = count;
}

void SceneViewerScreen::UpdateTotalCount()
{
	int count = 0;
	for (int i = 0; i < SceneManager::Get()->GetSceneCount(); i++) {
		count += SceneManager::Get()->GetScene(i)->GetTotalCount();
	}
	totalCount = count;
	SceneManager::Get()->allTotalCount = count;
}

void SceneViewerScreen::ResetViewAll()
{
	SceneManager::Get()->combinedObjectList->clear();
	isUpdated = false;
}
