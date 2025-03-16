#pragma once
#include <memory>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/matrix4x4.h>
#include "glm/fwd.hpp"

struct Vertex;
class Mesh;

class ModelParser
{
private:
    static const char* m_DebugName;

public:
    static void Fallback(std::vector<std::shared_ptr<Mesh>>& meshes);
    static bool ParseModel(const char* assetPath, std::vector<std::shared_ptr<Mesh>>& meshes);
    static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<std::shared_ptr<Mesh>>& meshes);
    static std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene, const glm::mat4& transform);
    static void ComputeTangents(std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
};
