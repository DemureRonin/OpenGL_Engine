#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
    glGenFramebuffers(1, &m_RendererID);
    Bind();

    glGenTextures(1, &m_ColorBufferID);
    glBindTexture(GL_TEXTURE_2D, m_ColorBufferID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorBufferID, 0);
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_RendererID);
}

void FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
}

void FrameBuffer::BindTextureBuffer() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_ColorBufferID);
}

void FrameBuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int FrameBuffer::CheckFBOStatus()
{
    unsigned int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << '\n';
    return status;
}
