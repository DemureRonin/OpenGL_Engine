#include "Renderer.h"
#include "../Utils/Colors.h"
bool Renderer::polygonMode = false;
glm::vec4 Renderer::color = COLOR_SKY_BLUE;

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
