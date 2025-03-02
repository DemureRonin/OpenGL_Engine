#include "VertexArray.h"



VertexArray::VertexArray() {
  glGenVertexArrays(1, &m_RendererID);
}
VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_RendererID); }
void VertexArray::Bind() const {
  glBindVertexArray(m_RendererID);
}
void VertexArray::Unbind() const {
  glBindVertexArray(0);
}
void VertexArray::AddVertexBuffer(VertexBuffer &vertexBuffer,
                                  VertexBufferLayout &layout) const {
  Bind();
  vertexBuffer.Bind();
  const auto &elements = layout.GetElements();
  unsigned int offset = 0;
  for (unsigned int i = 0; i < elements.size(); ++i) {
    const auto &element = elements[i];
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void *)offset);
    offset += element.count * sizeof(float);
    
  }
  Unbind();
  vertexBuffer.Unbind(); 
}