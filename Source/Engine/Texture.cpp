#include "Texture.h"

#include "stb_image_impl.h"

void Texture::LoadTexture()
{
    stbi_set_flip_vertically_on_load(true);
    m_LocalBuffer = stbi_load(assetPath.c_str(), &m_Width,
                              &m_Height, &m_BPP, 4);
    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (m_LocalBuffer)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, m_LocalBuffer);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(m_LocalBuffer);
    }
    else
    {
        std::cout << TEXTURE_LOG << "\033[31m Failed to load \033[0m" << assetPath << std::endl;
    }
    Unbind();
}

Texture::Texture(const std::string& filePath, Engine::GUID inGUID)
    : Asset(filePath, AssetType::Texture, inGUID), m_RendererID(0), m_LocalBuffer(nullptr), m_Width(0),
      m_Height(0),
      m_BPP(0)
{
    LoadTexture();
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
