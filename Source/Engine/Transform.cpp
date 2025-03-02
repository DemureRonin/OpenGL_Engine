#include "Transform.h"

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : position(position), rotation(rotation), scale(scale)
{
}

void Transform::SetPosition(glm::vec3 newPosition)
{
    this->position = newPosition;
    ApplyTranslation();
}

void Transform::SetRotation(glm::vec3 newRotation)
{
    this->rotation = newRotation;
    ApplyTranslation();
}

void Transform::SetScale(glm::vec3 newScale)
{
    this->scale = newScale;
    ApplyTranslation();
}

void Transform::ApplyTranslation()
{
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1)); // Z-axis
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0)); // Y-axis
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0)); // X-axis
    modelMatrix = glm::scale(modelMatrix, scale);
}
