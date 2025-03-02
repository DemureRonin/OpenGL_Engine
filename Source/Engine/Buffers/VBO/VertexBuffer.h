#pragma once
#include "glad/glad.h"
#include "../../ProgramObject.h"

class VertexBuffer  : public ProgramObject{
public:
  VertexBuffer(const void* data, unsigned int size);
  ~VertexBuffer() override;
  void Bind() const override;
  void Unbind() const override;
};
