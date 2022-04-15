#ifndef PHANTOM_ENGINE_ASSET_TYPES_H
#define PHANTOM_ENGINE_ASSET_TYPES_H

PH_NAMESPACE_BEGIN

enum class AssetFlag : ushort
{
    None = 0,
    Missing = BIT(0),
    Invalid = BIT(1)
};

enum class AssetType : ushort
{
    None = 0,
    Scene = 1,
    Prefab = 2,
    Mesh = 3,
    StaticMesh = 4,
    MeshSource = 5,
    Material = 6,
    Texture = 7,
    EnvMap = 8,
    Audio = 9,
    PhysicsMat = 10,
    SoundConfig = 11,
    SpatializationConfig = 12,
    Font = 13,

    //? Temp
    DemoGraph = 14
};

namespace utils {

    inline AssetType asset_type_from_string(const std::string& assetType)
    {
        if (assetType == "None")        return AssetType::None;
        if (assetType == "Scene")       return AssetType::Scene;
        if (assetType == "Prefab")      return AssetType::Prefab;
        if (assetType == "Mesh")        return AssetType::Mesh;
        if (assetType == "StaticMesh")  return AssetType::StaticMesh;
        if (assetType == "MeshAsset")   return AssetType::MeshSource; // DEPRECATED
        if (assetType == "MeshSource")  return AssetType::MeshSource;
        if (assetType == "Material")    return AssetType::Material;
        if (assetType == "Texture")     return AssetType::Texture;
        if (assetType == "EnvMap")      return AssetType::EnvMap;
        if (assetType == "Audio")       return AssetType::Audio;
        if (assetType == "PhysicsMat")  return AssetType::PhysicsMat;
        if (assetType == "SoundConfig") return AssetType::SoundConfig;
        if (assetType == "Font")        return AssetType::Font;

        //? Temp
        if (assetType == "DemoGraph") return AssetType::DemoGraph;

        Log::core_error("Unknown Asset Type");
        return AssetType::None;
    }

    inline const char* asset_type_to_string(AssetType asset_type)
    {
        switch (asset_type)
        {
            case AssetType::None:        return "None";
            case AssetType::Scene:       return "Scene";
            case AssetType::Prefab:      return "Prefab";
            case AssetType::Mesh:        return "Mesh";
            case AssetType::StaticMesh:  return "StaticMesh";
            case AssetType::MeshSource:  return "MeshSource";
            case AssetType::Material:    return "Material";
            case AssetType::Texture:     return "Texture";
            case AssetType::EnvMap:      return "EnvMap";
            case AssetType::Audio:       return "Audio";
            case AssetType::PhysicsMat:  return "PhysicsMat";
            case AssetType::SoundConfig: return "SoundConfig";
            case AssetType::Font:        return "Font";

                //? Temp
            case AssetType::DemoGraph: return "DemoGraph";
            case AssetType::SpatializationConfig: return "SpatializationConfig";
        }

        Log::core_error("Unknown Asset Type");
        return "None";
    }

}

PH_NAMESPACE_END

#endif //PHANTOM_ENGINE_ASSET_TYPES_H
