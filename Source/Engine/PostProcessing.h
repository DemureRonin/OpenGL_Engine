#pragma once
#include "Shader.h"
#include "Buffers/FBO/FrameBuffer.h"
#include "Buffers/RBO/RenderBufferObject.h"
#include "../Parsers/MeshParser.h"
#include "Object.h"

class PostProcessing
{
public:
    std::shared_ptr<Object> object;
    FrameBuffer FBO = FrameBuffer();
    RenderBufferObject RBO = RenderBufferObject();
    std::shared_ptr<Shader> postShader;
    PostProcessing();

    void RenderPostProcessing() const;
};
