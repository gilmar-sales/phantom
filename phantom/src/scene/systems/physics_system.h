#pragma once

#include <tuple>

#include <ecs/ecs.hpp>

#include "../components/transform_component.h"

PH_NAMESPACE_BEGIN

class PhysicsSystem : public ecs::BaseSystem<PhysicsSystem>
{
public:
    using Signature = std::tuple<TransformComponent>;

    PhysicsSystem() = default;
    ~PhysicsSystem() = default;

    template<typename Settings>
    void update(ecs::Manager<Settings>* manager)
    {
        for(ecs::EntityID entity : m_registered_entities)
        {
            TransformComponent& transform = manager->template get_component<TransformComponent>(entity);

            if (transform.position.x > 100000) {
                transform.position.x -= 1;
            }
            else {
                transform.position.x += 1;
            }
            transform.position.y += 1;
            transform.position.z += 1;

            // PH_CORE_INFO("phys process entity {}", entity);
        }
    }
};
    
PH_NAMESPACE_END
