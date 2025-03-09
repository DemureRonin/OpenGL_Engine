#pragma once
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Asset.h"
#include "EngineID/GUID.h"
#include "Mesh.h"

class Model : public Asset
{
public:
    Model(const std::string& path, Engine::GUID inGUID)
        : Asset(path, AssetType::Model, inGUID)
    {
        LoadModel();
    }

    ~Model() override = default;
   
    std::vector<std::shared_ptr<Mesh>> meshes;

private:
    void LoadModel();
    void ProcessNode(aiNode* node, const aiScene* scene);
    std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
    void ComputeTangents(std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
};
