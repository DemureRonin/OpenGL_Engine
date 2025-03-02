#pragma once
#include "GLFW/glfw3.h"

class Time
{
public:
    static void Tick();
    static float GetDeltaTime();
    static float GetTime();

private:
    static float m_DeltaTime;
    static float m_LastFrame;
};
