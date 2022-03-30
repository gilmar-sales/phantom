#pragma once

#include <ecs/ecs.hpp>
#include <renderer/scene_renderer.h>

#include "components/mesh_component.h"
#include "components/name_component.h"
#include "components/transform_component.h"
#include "systems/physics_system.h"
#include "systems/render_system.h"
#include "tags/tags.h"

PH_NAMESPACE_BEGIN

using ComponentList = std::tuple<NameComponent, TransformComponent, MeshComponent>;
using TagList = std::tuple<PlayerTag>;
using SystemList = std::tuple<PhysicsSystem, RenderSystem>;
using Settings = ecs::Settings<ComponentList, TagList, SystemList>;

class Scene
{
  public:
    Scene();
    ~Scene() = default;

    void update();
    
		void on_editor_render(shared<SceneRenderer> renderer, double ts);

    ecs::Manager<Settings> m_manager;
};

PH_NAMESPACE_END
