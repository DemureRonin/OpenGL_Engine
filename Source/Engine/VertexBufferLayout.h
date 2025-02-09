#pragma once
#include "glad/glad.h"

#include <vector>

struct VertexBufferLayoutElement {
  unsigned int type;
  unsigned int count;
  bool normalized;
};
class VertexBufferLayout {

private:
  std::vector<VertexBufferLayoutElement> m_Elements;
  unsigned int m_Stride;
public:
  VertexBufferLayout()
    : m_Stride(0) {}
  //number of elements in array data (uv, pos, normal)
 void Push(unsigned int type, unsigned int count) {
    m_Elements.push_back({type, count, false});
    m_Stride += sizeof(GLfloat) * count;
  }
  const std::vector<VertexBufferLayoutElement>& GetElements() const { return m_Elements; }
  unsigned int GetStride() const { return m_Stride; }
 
  
};

