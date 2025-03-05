#include "PostProcessing.h"


PostProcessing::PostProcessing()
{
    postShader = std::make_shared<Shader>("Source/Shaders/PostProcessing.glsl");
    postShader->Bind();
    postShader->SetInt("screenTexture", 0);

    std::string name = "d";
    object = std::make_shared<Object>(name);
    auto mesh = MeshParser::ParseMesh("Assets/Meshes/Mesh3.mesh");
    object->SetMesh(mesh);

    FBO.CheckFBOStatus();
    FBO.Unbind();
}

void PostProcessing::RenderPostProcessing() const
{
    FBO.Unbind();
    Renderer::EnableDepthTest(false);

    glClear(GL_COLOR_BUFFER_BIT);

    postShader->Bind();
    postShader->SetInt("screenTexture", 0);
    FBO.BindTextureBuffer();
    object->Draw();
}
