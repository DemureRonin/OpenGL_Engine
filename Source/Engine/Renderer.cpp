#include "Renderer.h"
#include "../Utils/Colors.h"
bool Renderer::polygonMode = false;
glm::vec4 Renderer::color = COLOR_DARK_GREY;

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

void Renderer::SetBackfaceCulling()
{
    glEnable(GL_CULL_FACE);

    // Set the culling mode to backface culling (default)
    glCullFace(GL_BACK);
}
