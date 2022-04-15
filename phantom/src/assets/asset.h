#ifndef PHANTOM_ENGINE_ASSET_H
#define PHANTOM_ENGINE_ASSET_H

#include <core/uuid.h>
#include <assets/asset_types.h>

PH_NAMESPACE_BEGIN

class Asset {
public:
    UUID handle;
    short flags = (short) AssetFlag::None;

    virtual ~Asset() {};

    bool is_valid();

    virtual bool operator==(const Asset& other) const
    {
        return handle == other.handle;
    }

    virtual bool operator!=(const Asset& other) const
    {
        return !(*this == other);
    }

    bool IsFlagSet(AssetFlag flag) const { return (uint16_t)flag & flags; }
    void SetFlag(AssetFlag flag, bool value = true)
    {
        if (value)
            flags |= (ushort)flag;
        else
            flags &= ~(ushort)flag;
    }
};

PH_NAMESPACE_END

#endif //PHANTOM_ENGINE_ASSET_H
