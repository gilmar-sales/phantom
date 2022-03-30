#pragma once

#include <glm/glm.hpp>

PH_NAMESPACE_BEGIN

struct NameComponent
{
    std::string name;

    NameComponent() = default;
    NameComponent(const NameComponent&) = default;
    NameComponent(const std::string& name)
        : name(name) {}
};

PH_NAMESPACE_END
