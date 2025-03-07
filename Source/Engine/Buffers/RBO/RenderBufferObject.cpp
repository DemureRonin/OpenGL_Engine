#include "RenderBufferObject.h"
#include "../../Source/Engine/Renderer.h"
#include "glad/glad.h"

RenderBufferObject::RenderBufferObject(int width, int height)
{
    glGenRenderbuffers(1, &m_RendererID);
    Bind();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RendererID);
}

RenderBufferObject::~RenderBufferObject()
{
    glDeleteRenderbuffers(1, &m_RendererID);
}

void RenderBufferObject::Bind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID);
}

void RenderBufferObject::Unbind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
