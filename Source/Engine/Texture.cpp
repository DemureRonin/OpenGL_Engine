#include "Texture.h"

#include "../Parsers/TextureParser.h"
#include "ConsoleDebug/ConsoleDebug.h"

Texture::Texture(const std::string& assetPath, Engine::GUID inGUID)
    : Asset(assetPath, AssetType::Texture, inGUID), m_RendererID(0), m_LocalBuffer(nullptr), m_Width(0),
      m_Height(0),
      m_BPP(0)
{
    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (!TextureParser::ParseTexture(GetAssetPath().c_str(), m_LocalBuffer, m_Width, m_Height, m_BPP))
    {
        ConsoleDebug::PrintError(m_DebugName, (std::string("Texture ") + assetPath + " failed to load").c_str());
        loadedSuccessfully = false;
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, m_LocalBuffer);
        glGenerateMipmap(GL_TEXTURE_2D);
        TextureParser::FreeBuffer(m_LocalBuffer);
    }
    Unbind();
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
