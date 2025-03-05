#pragma once
#include "glad/glad.h"
#include <string>
#include <iostream>
#define WHITE_TEXTURE "Textures/System/1x1_white.jpeg"
#define TEXTURE_LOG "[TEXTURE]"

enum TextureType
{
    ALBEDO = 0,
    NORMAL = 1,
    METALLIC = 2,
    ROUGHNESS = 3,
    SPECULAR = 4,
};

class Texture
{
private:
    unsigned int m_RendererID;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
    std::string m_FilePath;

public:
    TextureType m_Type;
    std::string GetFilePath() { return m_FilePath; }
    Texture(const std::string& filePath);
    ~Texture();
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
    unsigned int GetRendererID() const { return m_RendererID; }
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    TextureType GetType() const { return m_Type; }
    bool IsLoaded() const { return m_LocalBuffer != nullptr; }
};
