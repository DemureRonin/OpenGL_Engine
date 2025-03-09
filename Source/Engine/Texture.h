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

public:
    Texture(const std::string& filePath, Engine::GUID inGUID);
    ~Texture() override;
    
    void LoadTexture();
    std::string GetFilePath() { return assetPath; }
  
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
    unsigned int GetRendererID() const { return m_RendererID; }
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    bool IsLoaded() const { return m_LocalBuffer != nullptr; }
};
