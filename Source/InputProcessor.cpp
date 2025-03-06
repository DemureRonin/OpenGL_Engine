#include "InputProcessor.h"

#include <memory>

#include "Engine/Time/Time.h"

std::shared_ptr<Camera> InputProcessor::ipcamera = nullptr;
float InputProcessor::lastX = SCR_WIDTH / 2.0f;
float InputProcessor::lastY = SCR_HEIGHT / 2.0f;
bool InputProcessor::firstMouse = true;
bool InputProcessor::rightButtonPressed = false;
bool InputProcessor::shiftPressed = false;

void InputProcessor::InitCallbacks(GLFWwindow* window, const std::shared_ptr<Camera>& camera)
{
    ipcamera = camera;
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
}

void InputProcessor::MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (!rightButtonPressed) return;
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    ipcamera->ProcessMouseMovement(xoffset, yoffset);
}

void InputProcessor::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    ipcamera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void InputProcessor::ProcessInput(GLFWwindow* window, const std::shared_ptr<Camera>& camera)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera->ProcessKeyboard(FORWARD, Time::GetDeltaTime());
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera->ProcessKeyboard(BACKWARD, Time::GetDeltaTime());
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera->ProcessKeyboard(LEFT, Time::GetDeltaTime());
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera->ProcessKeyboard(RIGHT, Time::GetDeltaTime());
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        if (!rightButtonPressed)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            rightButtonPressed = true;
        }
    }
    else
    {
        if (rightButtonPressed)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            rightButtonPressed = false;
            firstMouse = true;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        if (!shiftPressed)
        {
            camera->MovementSpeed = 5;
            shiftPressed = true;
        }
    }
    else
    {
        if (shiftPressed)
        {
            camera->MovementSpeed = 10;
            shiftPressed = false;
        }
    }
}
