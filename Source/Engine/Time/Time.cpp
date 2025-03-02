#include "Time.h"

float Time::m_DeltaTime = 0;
float Time::m_LastFrame = 0;

void Time::Tick()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    m_DeltaTime = currentFrame - m_LastFrame;
    m_LastFrame = currentFrame;
}

float Time::GetDeltaTime()
{
    return m_DeltaTime;
}
float Time::GetTime()
{
    return static_cast<float>(glfwGetTime());
}
