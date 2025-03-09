#include "RenderTexture.h"

#include "Camera.h"
#include "Managers/AssetLoader.h"



RenderTexture::RenderTexture(const std::shared_ptr<Camera>& camera)
{
    this->camera = camera;
    /*auto it = AssetLoader::shaders.begin();
    std::advance(it, 1);
    postShader = it->second;
    std::cout << it->second->assetPath << std::endl;
    postShader->Bind();
    postShader->SetInt("screenTexture", 0);

    std::string name = "d";
    object = std::make_shared<Object>(name);
    auto mesh = AssetLoader::models.begin()->second;
    std::cout << mesh->assetPath << std::endl;
   // object->model = mesh;*/


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
    camera->SetAspect(width, height);
    Bind();
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
