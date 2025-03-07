#pragma once
#include "glad/glad.h"

class RenderBufferObject
{
private:
    unsigned int m_RendererID = 0;

public:
    RenderBufferObject(int width = 1600, int height = 900);
    ~RenderBufferObject();
 
    RenderBufferObject(const RenderBufferObject&) = delete;
    RenderBufferObject& operator=(const RenderBufferObject&) = delete;

  
    RenderBufferObject(RenderBufferObject&& other) noexcept
    {
        m_RendererID = other.m_RendererID;
        other.m_RendererID = 0; 
    }

 
    RenderBufferObject& operator=(RenderBufferObject&& other) noexcept
    {
        if (this != &other)
        {
            glDeleteRenderbuffers(1, &m_RendererID); 
            m_RendererID = other.m_RendererID;
            other.m_RendererID = 0; 
        }
        return *this;
    }

    void Bind() const;
    void Unbind() const;

    unsigned int GetRendererID() const
    {
        return m_RendererID;
    }
};
