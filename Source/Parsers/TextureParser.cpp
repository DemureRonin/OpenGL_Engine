#include "TextureParser.h"

#include <string>

#include "../Engine/stb_image_impl.h"
#include "../Engine/ConsoleDebug/ConsoleDebug.h"
#include "../Engine/Types.h"
#include "../Engine/Texture.h"
#include "../Engine/Managers/AssetLoader.h"
const char* TextureParser::m_DebugName = "TEXTURE_PARSER";

bool TextureParser::ParseTexture(const char* assetPath, unsigned char* & m_LocalBuffer, int& m_Width, int& m_Height,
                                 int& m_BPP)
{
    stbi_set_flip_vertically_on_load(true);
    m_LocalBuffer = stbi_load(assetPath, &m_Width,
                              &m_Height, &m_BPP, 4);
    if (m_LocalBuffer)
    {
        return true;
    }
    ConsoleDebug::PrintError(m_DebugName,
                             (std::string("Failed to load texure ") + std::string(assetPath)).c_str());

    return false;
}

void TextureParser::FreeBuffer(unsigned char*& m_LocalBuffer)
{
    stbi_image_free(m_LocalBuffer);
}
