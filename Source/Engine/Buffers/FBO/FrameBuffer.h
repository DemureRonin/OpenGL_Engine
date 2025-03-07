#pragma once
#include "glad/glad.h"
#include "../../Source/Engine/Renderer.h"

class FrameBuffer
{
private:
    unsigned int m_RendererID = 0;
    unsigned int m_ColorBufferID = 0;

public:
    FrameBuffer(int width = 1600, int height = 900);
    ~FrameBuffer();
    FrameBuffer(const FrameBuffer&) = delete;
    FrameBuffer& operator=(const FrameBuffer&) = delete;

    FrameBuffer(FrameBuffer&& other) noexcept
    {
        m_ColorBufferID = other.m_ColorBufferID;
        m_RendererID = other.m_RendererID;
        other.m_ColorBufferID = 0;
        other.m_RendererID = 0;
    }


    FrameBuffer& operator=(FrameBuffer&& other) noexcept
    {
        if (this != &other)
        {
            glDeleteFramebuffers(1, &m_RendererID);
            glDeleteTextures(1, &m_ColorBufferID);
            m_ColorBufferID = other.m_ColorBufferID;
            m_RendererID = other.m_RendererID;
            other.m_ColorBufferID = 0;
            other.m_RendererID = 0;
        }
        return *this;
    }

    void Bind() const;
    void BindTextureBuffer() const;
    void Unbind() const;
    unsigned int CheckFBOStatus();
    unsigned int GetColorBuffer() { return m_ColorBufferID; }

    unsigned int GetRendererID() const
    {
        return m_RendererID;
    }
};
