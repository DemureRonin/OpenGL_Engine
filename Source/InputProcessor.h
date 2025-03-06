#pragma once
#include <memory>

#include "Engine/Camera.h"
#include "Engine/Renderer.h"
#include "GLFW/glfw3.h"

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

class InputProcessor
{
public:
    static std::shared_ptr<Camera> ipcamera;
    static float lastX;
    static float lastY;
    static bool firstMouse;
    static bool rightButtonPressed;
    static bool shiftPressed;


    static void InitCallbacks(GLFWwindow* window, const std::shared_ptr<Camera>& camera);
    static void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);
    static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void ProcessInput(GLFWwindow* window, const std::shared_ptr<Camera>& camera);
};

inline void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    InputProcessor::MouseCallback(window, xposIn, yposIn);
}

inline void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    InputProcessor::ScrollCallback(window, xoffset, yoffset);
}
