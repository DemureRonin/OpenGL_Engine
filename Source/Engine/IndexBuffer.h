#pragma once
#include "ProgramObject.h"

class IndexBuffer : public ProgramObject {
private:
  unsigned int m_Count;
  
public:
  IndexBuffer(const unsigned int* data, unsigned int count);
  ~IndexBuffer() override;
  void Bind() const override;
  void Unbind() const override;
  unsigned int GetCount() const { return m_Count; }
};
