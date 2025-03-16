#pragma once
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>

class Transform {
public:
  Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
  glm::vec3 position = glm::vec3(0, 0, 0);
  glm::vec3 rotation = glm::vec3(0, 0, 0);
  glm::vec3 scale = glm::vec3(1, 1, 1);
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  void SetPosition(glm::vec3 newPosition);
  void SetRotation(glm::vec3 newRotation);
  void SetScale(glm::vec3 newScale);
   glm::mat4 ApplyTranslation(const glm::mat4& parent);
};
