#pragma once
#include "Buffers/EBO/IndexBuffer.h"
#include "Shader.h"
#include "Buffers/VAO/VertexArray.h"
#include <glm/glm.hpp>


#define SCR_WIDTH  1600
#define SCR_HEIGHT  900

class Renderer
{
public:
    static bool polygonMode;
    static glm::vec4 color;
    static void EnableDepthTest(bool vl);
    static void SetPolygonMode();
    static void Clear();
    static void SetBackfaceCulling();
};
