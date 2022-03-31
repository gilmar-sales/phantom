#include "scene.h"

PH_NAMESPACE_BEGIN

Scene::Scene(): m_manager(1024u) {
    auto camera = m_manager.create_entity();

    m_manager.add_component(camera, NameComponent{"Main Camera"});
    m_manager.add_tag<MainCameraTag>(camera);
    m_manager.add_component(camera, TransformComponent{});
}

void Scene::update()
{
    Log::core_info("scene update");
    m_manager.update();
}

void Scene::on_editor_render(shared<SceneRenderer> renderer, double ts)
{

}

PH_NAMESPACE_END
