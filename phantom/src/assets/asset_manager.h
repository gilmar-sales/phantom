#ifndef PHANTOM_ENGINE_ASSET_MANAGER_H
#define PHANTOM_ENGINE_ASSET_MANAGER_H

#include "asset_registry.h"

PH_NAMESPACE_BEGIN

// Deserialized from project file - these are just defaults
class AssetManagerConfig
{
    std::string asset_path = "Assets/";
    std::string asset_registry_path = "Assets/AssetRegistry.hzr";

    std::string mesh_path = "Assets/Meshes/";
    std::string mesh_source_path = "Assets/Meshes/Source/";
};

class AssetManager {

};

PH_NAMESPACE_END

#endif //PHANTOM_ENGINE_ASSET_MANAGER_H
