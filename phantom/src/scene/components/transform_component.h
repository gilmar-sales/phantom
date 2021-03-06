#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

PH_NAMESPACE_BEGIN

struct TransformComponent
{
    glm::vec3 position{};
    glm::vec3 scale{1, 1, 1};
    glm::quat rotation{1,  0, 0, 0};
};
    
PH_NAMESPACE_END
