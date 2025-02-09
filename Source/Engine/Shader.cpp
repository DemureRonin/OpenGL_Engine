#include "Shader.h"
Shader::Shader(const char *filePath) {
  const auto shaderSource = ParseShader(filePath);

  const char *vShaderCode = shaderSource.vertex.c_str();
  const char *fShaderCode = shaderSource.fragment.c_str();

  unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  CheckCompileErrors(vertex, "VERTEX");

  unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  CheckCompileErrors(fragment, "FRAGMENT");

  m_RendererID = glCreateProgram();
  glAttachShader(m_RendererID, vertex);
  glAttachShader(m_RendererID, fragment);
  glLinkProgram(m_RendererID);
  CheckCompileErrors(m_RendererID, "PROGRAM");

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::Bind() const { glUseProgram(m_RendererID); }
void Shader::Unbind() const { glUseProgram(0); }

void Shader::SetBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void Shader::SetVec3(const std::string &name, float v1, float v2,
                     float v3) const {
  glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), v1, v2, v3);
}
void Shader::SetVec3(const std::string &name,glm::vec3 vec3) const {
  glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), vec3.x, vec3.y, vec3.z);
}
void Shader::SetMat4(glm::mat4 mat4, std::string name) const {
  glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1,
                     GL_FALSE, glm::value_ptr(mat4));
}

void Shader::SetVec4(const std::string &name, glm::vec4 vec4) const
{
  glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), vec4.x, vec4.y, vec4.z, vec4.w);
}

Shader::ShaderProgramSource Shader::ParseShader(const std::string &filePath) {
  enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2 };
  ShaderType type = ShaderType::NONE;
  std::ifstream stream(filePath);
  std::string line;
  std::stringstream stringStream[2];
  while (std::getline(stream, line)) {
    if (line.find("#pragma") != std::string::npos) {
      if (line.find("vertex") != std::string::npos) {
        type = ShaderType::VERTEX;
      } else if (line.find("fragment") != std::string::npos) {
        type = ShaderType::FRAGMENT;
      }
    } else {
      stringStream[(int)type] << line << '\n';
    }
  }
  return {stringStream[0].str(), stringStream[1].str()};
}
void Shader::CheckCompileErrors(unsigned int shader, std::string type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cout
          << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cout
          << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  }
}