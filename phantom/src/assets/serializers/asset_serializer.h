
#ifndef PHANTOM_ENGINE_ASSET_SERIALIZER_H
#define PHANTOM_ENGINE_ASSET_SERIALIZER_H

#include <assets/asset_metadata.h>

PH_NAMESPACE_BEGIN

class AssetSerializer
{
public:
    virtual void serialize(const AssetMetadata& metadata, const shared<Asset>& asset) const = 0;
    virtual bool deserialize(const AssetMetadata& metadata, shared<Asset>& asset) const = 0;
};

PH_NAMESPACE_END

#endif //PHANTOM_ENGINE_ASSET_SERIALIZER_H
