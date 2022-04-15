#ifndef PHANTOM_ENGINE_ASSET_REGISTRY_H
#define PHANTOM_ENGINE_ASSET_REGISTRY_H

#include <assets/asset_metadata.h>

#include <unordered_map>
#include <filesystem>

namespace std {

    template <>
    struct hash<std::filesystem::path>
    {
        std::size_t operator()(const std::filesystem::path& path) const
        {
            return hash_value(path);
        }
    };

}

PH_NAMESPACE_BEGIN

class AssetRegistry {

public:
    std::filesystem::path get_path_key(const std::filesystem::path& path) const;

    AssetMetadata& operator[](const std::filesystem::path& path);
    const AssetMetadata& get(const std::filesystem::path& path) const;

    size_t size() const { return m_AssetRegistry.size(); }
    bool contains(const std::filesystem::path& path) const;
    size_t remove(const std::filesystem::path& path);
    void clear();

    std::unordered_map<std::filesystem::path, AssetMetadata>::iterator begin() { return m_AssetRegistry.begin(); }
    std::unordered_map<std::filesystem::path, AssetMetadata>::iterator end() { return m_AssetRegistry.end(); }
    std::unordered_map<std::filesystem::path, AssetMetadata>::const_iterator cbegin() const { return m_AssetRegistry.cbegin(); }
    std::unordered_map<std::filesystem::path, AssetMetadata>::const_iterator cend() const { return m_AssetRegistry.cend(); }
private:
    std::unordered_map<std::filesystem::path, AssetMetadata> m_AssetRegistry;
};

PH_NAMESPACE_END

#endif //PHANTOM_ENGINE_ASSET_REGISTRY_H
