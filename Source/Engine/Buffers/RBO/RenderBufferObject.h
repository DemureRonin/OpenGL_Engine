#pragma once

class RenderBufferObject
{
private:
    unsigned int m_RendererID = 0;
    

public:
    RenderBufferObject();
    ~RenderBufferObject();
    void Bind() const;
    void Unbind() const;

    unsigned int GetRendererID() const
    {
        return m_RendererID;
    }
};
