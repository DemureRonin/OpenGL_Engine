#include "ModelParser.h"

#include "glm/vec3.hpp"
#include "../Engine/ConsoleDebug/ConsoleDebug.h"
#include "../Engine/Mesh.h"
#include "../Engine/Model.h"
#include "../Engine/Types.h"
#include "../Engine/Managers/AssetLoader.h"
class Texture;
const char* ModelParser::m_DebugName = "MODEL_PARSER";

void ModelParser::Fallback(std::vector<std::shared_ptr<Mesh>>& meshes)
{
    auto fallbackModel = TYPEOF(Model)(AssetLoader::GetAsset(Engine::GUID::FromString(MODEL_ERROR)));
    meshes.push_back(fallbackModel->meshes[0]);
}

bool ModelParser::ParseModel(const char* assetPath, std::vector<std::shared_ptr<Mesh>>& meshes)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(assetPath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        ConsoleDebug::PrintError(m_DebugName, import.GetErrorString());
        Fallback(meshes);
        return false;
    }

    ProcessNode(scene->mRootNode, scene, meshes);
    return true;
}

void ModelParser::ProcessNode(aiNode* node, const aiScene* scene, std::vector<std::shared_ptr<Mesh>>& meshes)
{
    // Convert Assimp transformation matrix to glm
    aiMatrix4x4 aiTransform = node->mTransformation;
    glm::mat4 transform = glm::mat4(
        aiTransform.a1, aiTransform.b1, aiTransform.c1, aiTransform.d1,
        aiTransform.a2, aiTransform.b2, aiTransform.c2, aiTransform.d2,
        aiTransform.a3, aiTransform.b3, aiTransform.c3, aiTransform.d3,
        aiTransform.a4, aiTransform.b4, aiTransform.c4, aiTransform.d4
    );

    glm::vec3 rootScale = glm::vec3(scene->mRootNode->mTransformation.a1,
                                    scene->mRootNode->mTransformation.b2,
                                    scene->mRootNode->mTransformation.c3);
    transform = glm::scale(transform, 1.0f / rootScale);
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene, transform)); 
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene, meshes);
    }
}

std::shared_ptr<Mesh> ModelParser::ProcessMesh(aiMesh* mesh, const aiScene* scene, const glm::mat4& transform)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec4 pos(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z, 1.0f);
        vertex.Position = glm::vec3(transform * pos); // Apply transform

        if (mesh->HasNormals())
        {
            glm::vec4 normal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z, 0.0f);
            vertex.Normal = glm::normalize(glm::vec3(transform * normal));
        }

        if (mesh->mTextureCoords[0])
            vertex.UV = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        else
            vertex.UV = glm::vec2(0.0f);

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    return std::make_shared<Mesh>(vertices, indices);
}


void ModelParser::ComputeTangents(std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    for (size_t i = 0; i < indices.size(); i += 3)
    {
        // Get triangle vertices
        Vertex& v0 = vertices[indices[i]];
        Vertex& v1 = vertices[indices[i + 1]];
        Vertex& v2 = vertices[indices[i + 2]];

        // Get position differences
        glm::vec3 deltaPos1 = v1.Position - v0.Position;
        glm::vec3 deltaPos2 = v2.Position - v0.Position;

        // Get UV differences
        glm::vec2 deltaUV1 = v1.UV - v0.UV;
        glm::vec2 deltaUV2 = v2.UV - v0.UV;

        // Compute tangent and bitangent
        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
        glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

        // Assign computed values to each vertex of the triangle
        v0.Tangent += tangent;
        v1.Tangent += tangent;
        v2.Tangent += tangent;

        v0.Bitangent += bitangent;
        v1.Bitangent += bitangent;
        v2.Bitangent += bitangent;
    }


    for (Vertex& v : vertices)
    {
        v.Tangent = glm::normalize(v.Tangent);
        v.Bitangent = glm::normalize(v.Bitangent);
    }
}
