#pragma once
#include "Buffers/EBO/IndexBuffer.h"
#include "Shader.h"
#include "Buffers/VAO/VertexArray.h"
#include <glm/glm.hpp>

#include "GLFW/glfw3.h"


#define SCR_WIDTH  1600
#define SCR_HEIGHT  900

class Renderer
{
private:
    static glm::ivec2 m_Viewport;
    static bool m_ViewportSizeChanged;

public:
    static GLFWwindow* currentWindow;
    static bool polygonMode;
    static glm::vec4 color;
    static void EnableDepthTest(bool vl);
    static void SetPolygonMode();
    static void Clear();
    static void SetBackfaceCulling(bool vl);
    static void NewFrame();
    static void SetViewport(int x, int y, int width, int height);
    static glm::vec2 GetViewport();
    static void SetWindow(GLFWwindow* window) { currentWindow = window; }
    static GLFWwindow* GetWindow() { return currentWindow; }
    static void ClearColorBit();
    static bool ChangedViewportSize() { return m_ViewportSizeChanged; }
};
