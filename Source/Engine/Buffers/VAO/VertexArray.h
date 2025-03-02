#pragma once
#include "../../ProgramObject.h"
#include "../VBO/VertexBuffer.h"
#include "../VertexBufferLayout.h"

class VertexArray : public ProgramObject {

public:
  VertexArray();
  ~VertexArray() override ;
  void Bind() const override ;
  void Unbind() const override;
  void AddVertexBuffer(VertexBuffer &vertexBuffer, VertexBufferLayout &layout) const;
};
