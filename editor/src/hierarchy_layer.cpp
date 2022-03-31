    //
// Created by gilmar on 30/03/2022.
//

#include "hierarchy_layer.h"

#include <utility>
#include <imgui.h>

PH_NAMESPACE_BEGIN

HierarchyLayer::HierarchyLayer(shared<Scene> scene): scene(scene) {
    for (unsigned i = 0; i < 10; i++)
    {
        auto entity = scene->m_manager.create_entity();
        std::stringstream entity_name;
        entity_name << "Empty(" << i << ")";

        auto &name = scene->m_manager.add_component<NameComponent>(entity);
        name = entity_name.str();
        scene->m_manager.add_component<TransformComponent>(entity);
    }
}

void HierarchyLayer::on_update() {
}

void HierarchyLayer::on_gui_render() {
    ImGui::Begin("Hierarchy");

    if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
    {
        selectionContext = 999999;
        Log::core_trace("select entity {}", selectionContext);
    }

    scene->m_manager.for_each([&](auto entityID) { draw_entity_node(entityID); });

    // context menu
    if (ImGui::BeginPopupContextWindow(0, 1, false))
    {
        if (ImGui::MenuItem("Empty entity"))
        {
            auto entity = scene->m_manager.create_entity();

            auto &name = scene->m_manager.add_component<NameComponent>(entity);
            name.name = "Entity";
            ImGui::BulletText("Return to input text into a widget.");
            if (!ImGui::IsPopupOpen("popup"))
                ImGui::OpenPopup("popup");
        }

        if (ImGui::BeginMenu("3D Entity"))
        {
            if (ImGui::MenuItem("Cube"))
            { /* Do stuff */
            }
            if (ImGui::MenuItem("Sphere"))
            { /* Do stuff */
            }
            if (ImGui::MenuItem("Capsule"))
            { /* Do stuff */
            }
            ImGui::EndMenu();
        }

        if (ImGui::MenuItem("Camera"))
        { /* Do stuff */
        }
        if (ImGui::MenuItem("Terrain"))
        { /* Do stuff */
        }

        ImGui::EndPopup();
    }

    ImGui::End();

    ImGui::Begin("Components");

    if (scene->m_manager.get_next_entity() > selectionContext)
        draw_components();

    ImGui::End();
}

void HierarchyLayer::draw_entity_node(unsigned int entity) {
    std::string_view tag = scene->m_manager.get_component<NameComponent>(entity).name;

    ImGuiTreeNodeFlags flags =
            ((selectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
    flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
    bool opened = ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)entity, flags, tag.data());
    if (ImGui::IsItemClicked() | ImGui::IsItemClicked(1))
    {
        selectionContext = entity;
        Log::core_info("select entity {}", selectionContext);
    }

    bool entityDeleted = false;
    if (ImGui::BeginPopupContextItem())
    {
        auto& name = scene->m_manager.get_component<NameComponent>(entity).name;

        if (ImGui::MenuItem("Delete Entity"))
            entityDeleted = true;

        if (ImGui::MenuItem("Add transform"))
        {
            scene->m_manager.add_component<TransformComponent>(entity);
            Log::core_info("Add transform component to {}", name);
        }

        if (ImGui::MenuItem("Add mesh"))
        {
            add_mesh(entity);
            Log::app_info("Add mesh component to {}", name);
        }

        ImGui::EndPopup();
    }

    if (opened)
    {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
        bool opened = ImGui::TreeNodeEx((void *)9817239, flags, tag.data());
        if (opened)
            ImGui::TreePop();
        ImGui::TreePop();
    }

    if (entityDeleted)
    {
        scene->m_manager.destroy_entity(entity);
        if (selectionContext == entity)
            selectionContext = -1;
    }
}

    void HierarchyLayer::draw_components() {
        if (scene->m_manager.has_component<TransformComponent>(selectionContext)) {
            auto& transform = scene->m_manager.get_component<TransformComponent>(selectionContext);
            ImGui::Begin("Transform Component", nullptr, ImGuiWindowFlags_ChildWindow);
                ImGui::DragFloat3("Position", &transform.position[0], 0.1f);
                ImGui::DragFloat4("Rotation", &transform.rotation[0], 0.1f);
                ImGui::DragFloat3("Scale", &transform.scale[0], 0.1f);
            ImGui::End();
        }

        if (scene->m_manager.has_component<MeshComponent>(selectionContext)) {
            ImGui::Begin("Mesh Component", nullptr, ImGuiWindowFlags_ChildWindow);

            ImGui::End();
        }
    }

void HierarchyLayer::add_mesh(unsigned int entity) {
    scene->m_manager.add_component<MeshComponent>(entity);
}

PH_NAMESPACE_END