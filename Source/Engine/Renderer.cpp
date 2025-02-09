#include "Renderer.h"
void Renderer::Render(const VertexArray &VAO, const IndexBuffer &EBO,
                      const Shader &shader) const {
  shader.Bind();
  VAO.Bind();
  EBO.Bind();
  glDrawElements(GL_TRIANGLES, EBO.GetCount(), GL_UNSIGNED_INT, nullptr);
}
void Renderer::Clear(glm::vec4 color) const {
  glClearColor(color.x, color.y, color.z, color.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
 