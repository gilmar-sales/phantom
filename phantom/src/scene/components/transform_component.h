#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

PH_NAMESPACE_BEGIN

struct TransformComponent
{
    glm::vec3 position;
    glm::vec3 scale;
    glm::quat rotation;
};
    
PH_NAMESPACE_END
