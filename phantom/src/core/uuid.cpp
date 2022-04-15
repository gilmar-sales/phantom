#include "uuid.h"

#include <random>

static std::random_device s_RandomDevice;
static std::mt19937_64  eng(s_RandomDevice());
static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

PH_NAMESPACE_BEGIN
UUID::UUID()
        : m_UUID(s_UniformDistribution(eng))
{
}

UUID::UUID(ulong uuid)
        : m_UUID(uuid)
{
}

UUID::UUID(const UUID& other)
        : m_UUID(other.m_UUID)
{
}
PH_NAMESPACE_END