#ifndef SHADER_H
#define SHADER_H

#include "ProgramObject.h"

#include <glad/glad.h>

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>

class Shader : public ProgramObject {
#define SHADER_LIT "Source/Shaders/Lit.glsl"
#define SHADER_UNLIT "Source/Shaders/Unlit.glsl"
public:
  Shader(const char *filePath = SHADER_LIT);
  void Bind() const override;
  void Unbind() const override;
  void SetBool(const std::string &name, bool value) const;
  void SetInt(const std::string &name, int value) const;
  void SetFloat(const std::string &name, float value) const;
  void SetVec3(const std::string &name, float v1, float v2, float v3) const;
  void SetVec3(const std::string &name, glm::vec3 vec3) const;
  void SetMat4(glm::mat4 mat4, std::string name) const;
  void SetVec4(const std::string &name, glm::vec4 vec4) const;

private:
  struct ShaderProgramSource {
    std::string vertex, fragment;
  };
  ShaderProgramSource ParseShader(const std::string &filePath);
  void CheckCompileErrors(unsigned int shader, std::string type);
};
#endif