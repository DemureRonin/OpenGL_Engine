#include "RenderTexture.h"

#include "Camera.h"
#include "Managers/ShaderManager.h"


RenderTexture::RenderTexture()
{
    postShader = ShaderManager::GetShader("Source/Shaders/PostProcessing.glsl");
    postShader->Bind();
    postShader->SetInt("screenTexture", 0);

    std::string name = "d";
    object = std::make_shared<Object>(name);
    auto mesh = MeshParser::ParseMesh("Assets/Meshes/Mesh3.mesh");
    object->SetMesh(mesh);

    FBO.CheckFBOStatus();
    FBO.Unbind();
}

void RenderTexture::RenderPostProcessing() const
{
    /*FBO.Unbind();
    Renderer::SetBackfaceCulling(false);
    Renderer::EnableDepthTest(false);

    glClear(GL_COLOR_BUFFER_BIT);
    BindTexture();*/
    postShader->Bind();
    postShader->SetInt("screenTexture", 0);
    //   FBO.BindTextureBuffer();
    object->Draw();
}

void RenderTexture::NewFrame(int width, int height)
{
  auto size = Renderer::GetViewport();
    if (Renderer::ChangedViewportSize())
    {
        FBO = FrameBuffer(size.x, size.y);
        RBO = RenderBufferObject(size.x, size.y);
    }
}

void RenderTexture::BindTexture() const
{
    FBO.Unbind();
    Renderer::SetBackfaceCulling(false);
    Renderer::EnableDepthTest(false);
    Renderer::ClearColorBit();
    FBO.BindTextureBuffer();
}

void RenderTexture::Bind() const
{
    FBO.Bind();
}
