#pragma once
#include "Buffers/EBO/IndexBuffer.h"
#include "Shader.h"
#include "Buffers/VAO/VertexArray.h"
#include <glm/glm.hpp>


#define SCR_WIDTH  1920
#define SCR_HEIGHT  1080

class Renderer
{
public:
    static bool polygonMode;
    static glm::vec4 color;
    static void SetPolygonMode();
    static void Clear();
};
