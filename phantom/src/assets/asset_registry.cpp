#include "asset_registry.h"

PH_NAMESPACE_BEGIN

#define PH_ASSETREGISTRY_LOG 1
#if PH_ASSETREGISTRY_LOG
#define ASSET_LOG(...) Log::core_fatal(__VA_ARGS__)
#else
#define ASSET_LOG(...)
#endif

std::filesystem::path AssetRegistry::get_path_key(const std::filesystem::path& path) const
{
    auto key = std::filesystem::relative(path, "./");
    if (key.empty())
        key = path.lexically_normal();

    return key;
}

AssetMetadata& AssetRegistry::operator[](const std::filesystem::path& path)
{
    auto key = get_path_key(path);
    ASSET_LOG("[ASSET] Retrieving key {0} (path = {1})", key.string(), path.string());
    //HZ_CORE_ASSERT(!path.string().empty());
    return m_AssetRegistry[key];
}

const AssetMetadata& AssetRegistry::get(const std::filesystem::path& path) const
{
    auto key = get_path_key(path);
    //HZ_CORE_ASSERT(m_AssetRegistry.find(key) != m_AssetRegistry.end());
    ASSET_LOG("[ASSET] Retrieving const {0} (path = {1})", key.string(), path.string());
    //HZ_CORE_ASSERT(!path.string().empty());
    return m_AssetRegistry.at(key);
}



bool AssetRegistry::contains(const std::filesystem::path& path) const
{
    auto key = get_path_key(path);
    ASSET_LOG("[ASSET] Contains key {0} (path = {1})", key.string(), path.string());
    return m_AssetRegistry.find(key) != m_AssetRegistry.end();
}

size_t AssetRegistry::remove(const std::filesystem::path& path)
{
    auto key = get_path_key(path);
    ASSET_LOG("[ASSET] Removing key {0} (path = {1})", key.string(), path.string());
    return m_AssetRegistry.erase(key);
}

void AssetRegistry::clear()
{
    ASSET_LOG("[ASSET] Clearing registry");
    m_AssetRegistry.clear();
}

PH_NAMESPACE_END