#pragma once
#include "Shader.h"
#include "Buffers/FBO/FrameBuffer.h"
#include "Buffers/RBO/RenderBufferObject.h"
#include "Prefab.h"

class RenderTexture
{
public:
    std::shared_ptr<Prefab> object;
    FrameBuffer FBO = FrameBuffer();
    RenderBufferObject RBO = RenderBufferObject();
    std::shared_ptr<Shader> postShader;
    std::shared_ptr<Camera> camera;
    RenderTexture(const std::shared_ptr<Camera>& camera);

    void RenderPostProcessing() const;
    void NewFrame(int width, int height);
    void BindTexture() const;
    void Bind() const;
};
