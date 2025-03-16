#pragma once

class TextureParser
{
private:
    static const char* m_DebugName;

public:
    static bool ParseTexture(const char* assetPath, unsigned char* & m_LocalBuffer, int& m_Width, int& m_Height,
                             int& m_BPP);
    static void FreeBuffer(unsigned char*& m_LocalBuffer);
};
