#pragma once
#include "UIScreen.h"
class FPSCounter : public UIScreen
{
public:
    // Inherited via UIScreen
    virtual void DrawUI() override;
    void CalculateFPS();
    FPSCounter();
    ~FPSCounter();
private:
    std::string fpsText;
    float ticks = 0.0f;
};

