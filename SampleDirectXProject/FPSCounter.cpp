#include "FPSCounter.h"
#include "EngineTime.h"

FPSCounter::FPSCounter() : UIScreen("FPSCounter", true)
{
}

FPSCounter::~FPSCounter()
{
}
void FPSCounter::DrawUI()
{
	// Create ImGui Window;
	ImGui::Begin("FPS Counter", &isActive, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
	
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 255, 255));
	CalculateFPS();
	ImGui::Text(fpsText.c_str());
	ImGui::PopStyleColor();

	ImGui::End();
}

void FPSCounter::CalculateFPS()
{
	float currentTime = EngineTime::getDeltaTime();
	this->ticks += EngineTime::getDeltaTime();
	if (ticks >= 0.5f) {
		fpsText = "FPS: " + std::to_string(1.0f / currentTime);
		ticks = 0.0f;
	}
}


