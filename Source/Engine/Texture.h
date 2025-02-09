#pragma once
#include <string>

class Texture {

private:
  unsigned int m_RendererID;
  std::string m_FilePath;
  unsigned char * m_LocalBuffer;
  int m_Width, m_Height, m_BPP;
public:
  Texture(const std::string& filePath);
  ~Texture();
  void Bind(unsigned int slot = 0) const;
  void Unbind() const;
  unsigned int GetRendererID() const { return m_RendererID; }
  int GetWidth() const { return m_Width; }
  int GetHeight() const { return m_Height; }
};
