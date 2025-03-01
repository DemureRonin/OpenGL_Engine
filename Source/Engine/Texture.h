#pragma once
#include <string>
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
  

public:
    TextureType m_Type;
    std::string m_FilePath;
    Texture(const std::string& filePath);
    ~Texture();
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
    unsigned int GetRendererID() const { return m_RendererID; }
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    TextureType GetType() const { return m_Type; }
};
