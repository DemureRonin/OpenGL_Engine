#pragma once
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

class Renderer {
public:
  void Render(const VertexArray& VAO,const IndexBuffer& EBO, const Shader& shader) const;
  void Clear(glm::vec4 color = glm::vec4(0)) const;
  
};
