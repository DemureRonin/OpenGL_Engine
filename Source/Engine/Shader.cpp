#include "Shader.h"

#include "Camera.h"
#include "Material.h"
#include "Prefab.h"
#include "ShaderParams.h"
#include "../Parsers/ShaderParser.h"


Shader::Shader(const std::string& filePath, Engine::GUID inGUID): Asset(filePath, AssetType::Shader, inGUID)
{
    const auto shaderSource = ShaderParser::ParseShaderFile(filePath.c_str());

    const char* vShaderCode = shaderSource.vertex.c_str();
    const char* fShaderCode = shaderSource.fragment.c_str();

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    loadedSuccessfully &= ShaderParser::CheckCompileErrors(vertex, "VERTEX");

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    loadedSuccessfully &= ShaderParser::CheckCompileErrors(fragment, "FRAGMENT");

    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, vertex);
    glAttachShader(m_RendererID, fragment);
    glLinkProgram(m_RendererID);
    loadedSuccessfully &= ShaderParser::CheckCompileErrors(m_RendererID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void Shader::SetVec2(const std::string& name, glm::vec2 vec2) const
{
    glUniform2f(glGetUniformLocation(m_RendererID, name.c_str()), vec2.x, vec2.y);
}


void Shader::SetVec3(const std::string& name, float v1, float v2,
                     float v3) const
{
    glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), v1, v2, v3);
}

void Shader::SetVec3(const std::string& name, glm::vec3 vec3) const
{
    glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), vec3.x, vec3.y, vec3.z);
}

void Shader::SetMat4(glm::mat4 mat4, std::string name) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1,
                       GL_FALSE, glm::value_ptr(mat4));
}

void Shader::SetVec4(const std::string& name, glm::vec4 vec4) const
{
    glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), vec4.x, vec4.y, vec4.z, vec4.w);
}

void Shader::SetMaterialUniforms(const std::shared_ptr<Material>& material) const
{
    std::shared_ptr<ShaderParams> params = material->shaderParams;

    for (const auto& floatParam : params->floatParameters)
    {
        std::string paramName = "material." + floatParam.first;
        SetFloat(paramName, floatParam.second);
    }

    for (const auto& intParam : params->intParameters)
    {
        std::string paramName = "material." + intParam.first;
        SetInt(paramName, intParam.second);
    }

    int textureSlot = 0;
    for (const auto& texturePair : params->textureParameters)
    {
        if (texturePair.second)
        {
            std::string paramName = "material." + texturePair.first;
            texturePair.second->Bind(textureSlot);
            SetInt(paramName, textureSlot);
        }
        textureSlot++;
    }

    for (const auto& vec2Param : params->vec2Parameters)
    {
        std::string paramName = "material." + vec2Param.first;
        SetVec2(paramName, vec2Param.second);
    }

    for (const auto& vec3Param : params->vec3Parameters)
    {
        std::string paramName = "material." + vec3Param.first;
        SetVec3(paramName, vec3Param.second);
    }

    for (const auto& vec4Param : params->vec4Parameters)
    {
        std::string paramName = "material." + vec4Param.first;
        SetVec4(paramName, vec4Param.second);
    }
}

void Shader::SetCameraUniforms(const Camera& camera)
{
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
                                            static_cast<float>(camera.aspectX) / static_cast<float>(camera.aspectY),
                                            0.1f, 1000.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 MVPmat4 = projection * view;
    SetMat4(MVPmat4, "MVPmat4");
}

void Shader::SetObjectUniforms(const Camera& camera, const Prefab& object) const
{
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
                                            static_cast<float>(camera.aspectX) / static_cast<float>(camera.aspectY),
                                            0.1f, 1000.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 Mmat4 = object.transform.modelMatrix;
    glm::mat4 Vmat4 = view;
    glm::mat4 MVmat4 = view * Mmat4;
    glm::mat4 MVPmat4 = projection * MVmat4;

    SetMat4(Mmat4, "Mmat4");
    SetMat4(Vmat4, "Vmat4");
    SetMat4(MVmat4, "MVmat4");
    SetMat4(MVPmat4, "MVPmat4");
    SetVec3("cameraPosition", camera.Position.x, camera.Position.y, camera.Position.z);
}

void Shader::SetDirectionalLightUniforms(const DirectionalLight& dirLight) const
{
    SetVec3("directionalLight.direction", dirLight.direction);
    SetVec3("directionalLight.ambient", dirLight.ambient);
    SetVec3("directionalLight.diffuse", dirLight.diffuse);
    SetVec3("directionalLight.specular", dirLight.specular);
}
