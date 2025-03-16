#pragma once
#include <vector>

#include "Asset.h"
#include "EngineID/GUID.h"
#include "Mesh.h"

class Model : public Asset
{
private:
    const char* m_DebugName = "MODEL";
public:
    Model(const std::string& assetPath, Engine::GUID inGUID);

    ~Model() override = default;
   
    std::vector<std::shared_ptr<Mesh>> meshes;
   
};
