#include "Model.h"
#include "../Parsers/ModelParser.h"
#include "Types.h"
#include "Managers/AssetLoader.h"

Model::Model(const std::string& assetPath, Engine::GUID inGUID)
    : Asset(assetPath, AssetType::Model, inGUID)
{
    if (!ModelParser::ParseModel(GetAssetPath().c_str(), meshes))
    {
        ConsoleDebug::PrintError(m_DebugName, (std::string("Model ") + assetPath + " failed to load").c_str());
        loadedSuccessfully = false;
    }
}
