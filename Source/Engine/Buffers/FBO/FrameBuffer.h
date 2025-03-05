#pragma once
#include "glad/glad.h"
#include "../../Source/Engine/Renderer.h"

class FrameBuffer
{
private:
    unsigned int m_RendererID = 0;
    unsigned int m_ColorBufferID = 0;

public:
    FrameBuffer();
    ~FrameBuffer();
    void Bind() const;
    void BindTextureBuffer() const;
    void Unbind() const;
    unsigned int CheckFBOStatus();

    unsigned int GetRendererID() const
    {
        return m_RendererID;
    }
};
