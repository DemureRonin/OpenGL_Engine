#pragma once
#include "glad/glad.h"
#include <string>
#include <iostream>

#include "Asset.h"
#define WHITE_TEXTURE "Assets/Textures/System/1x1_white.jpeg"
#define TEXTURE_LOG "[TEXTURE]"

class Texture : public Asset
{
private:
    unsigned int m_RendererID;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
    const char* m_DebugName = "TEXTURE";

public:
    Texture(const std::string& assetPath, Engine::GUID inGUID);
    ~Texture() override;

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
    unsigned int GetRendererID() const { return m_RendererID; }
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    unsigned char* GetLocalBuffer() const { return m_LocalBuffer; }
    int GetBPP() const { return m_BPP; }
    int GetWidth() { return m_Width; }
    int GetHeight() { return m_Height; }
};
