#ifndef PHANTOM_ENGINE_ASSET_METADATA_H
#define PHANTOM_ENGINE_ASSET_METADATA_H

#include <filesystem>

#include <assets/asset.h>

PH_NAMESPACE_BEGIN

struct AssetMetadata
{
    UUID handle = 0;
    AssetType Type;

    std::filesystem::path FilePath;
    bool IsDataLoaded = false;

    bool IsValid() const { return handle != 0; }
};

PH_NAMESPACE_END
#endif //PHANTOM_ENGINE_ASSET_METADATA_H
