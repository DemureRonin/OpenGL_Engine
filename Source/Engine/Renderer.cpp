#include "Renderer.h"

#include "Camera.h"
#include "Camera.h"
#include "../Utils/Colors.h"
#include "GLFW/glfw3.h"
bool Renderer::polygonMode = false;
glm::vec4 Renderer::color = COLOR_DARK_GREY;
GLFWwindow* Renderer::currentWindow = nullptr;
glm::ivec2 Renderer::m_Viewport = glm::ivec2(SCR_WIDTH, SCR_HEIGHT);
bool Renderer::m_ViewportSizeChanged = true;
void Renderer::EnableDepthTest(bool vl)
{
    if (vl)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
}

void Renderer::SetPolygonMode()
{
    if (polygonMode)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::Clear()
{
    glClearColor(color.x, color.y, color.z, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetBackfaceCulling(bool vl)
{
    if (vl)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }
}

void Renderer::NewFrame()
{
    int x, y;
    glfwGetFramebufferSize(currentWindow, &x, &y);
    if (x != m_Viewport.x || y != m_Viewport.y) {
       m_ViewportSizeChanged = true;
        SetViewport(0,0,x, y);
    }
    else
    {
        m_ViewportSizeChanged = false;
    }
    m_Viewport = glm::vec2(x, y);
}

void Renderer::SetViewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

glm::vec2 Renderer::GetViewport()
{
    return m_Viewport;
}

void Renderer::SetWindow(GLFWwindow* window)
{
    {
        currentWindow = window;
        NewFrame();
    }
}

void Renderer::ClearColorBit()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
