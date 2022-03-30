#include "hierarchy_panel.h"

#include <imgui.h>
#include <sstream>

namespace ph
{
static char entity_name[32] = "Empty";

HierarchyPanel::HierarchyPanel(std::shared_ptr<Scene> scene) : m_scene(scene)
{
    for (unsigned i = 0; i < 10; i++)
    {
        auto entity = m_scene->m_manager.create_entity();
        std::stringstream entity_name;
        entity_name << "Empty(" << i << ")";

        auto &name = m_scene->m_manager.add_component<NameComponent>(entity);
        name = entity_name.str();
        m_scene->m_manager.add_component<TransformComponent>(entity);
    }
}

int entity_name_callback(ImGuiInputTextCallbackData *data)
{
    strcpy(entity_name, data->Buf);

    return 0;
}

void HierarchyPanel::on_gui_render()
{
    ImGui::Begin("Hierarchy");

    if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
    {
        m_SelectionContext = 999999;
        PH_CORE_INFO("select entity {}", m_SelectionContext);
    }

    m_scene->m_manager.for_each([&](auto entityID) { draw_entity_node(entityID); });

    // context menu
    if (ImGui::BeginPopupContextWindow(0, 1, false))
    {
        if (ImGui::MenuItem("Empty entity"))
        {
            auto entity = m_scene->m_manager.create_entity();

            auto &name = m_scene->m_manager.add_component<NameComponent>(entity);
            name.name = entity_name;
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

    ImGui::Begin("Properties");
    /*
    if (m_SelectionContext)
        DrawComponents(m_SelectionContext);
    */

    ImGui::End();
    if (ImGui::BeginPopup("Popup", 0))
    {
        ImGuiTreeNodeFlags flags1 = ImGuiTreeNodeFlags_OpenOnArrow;
        flags1 |= ImGuiTreeNodeFlags_SpanAvailWidth;
        flags1 |= ImGuiTreeNodeFlags_AllowItemOverlap;
        ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)200, flags1, "Node test");

        ImGui::EndPopup();
    }
}

void HierarchyPanel::draw_entity_node(unsigned entity)
{
    std::string_view tag = m_scene->m_manager.get_component<NameComponent>(entity).name;

    ImGuiTreeNodeFlags flags =
        ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
    flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
    bool opened = ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)entity, flags, tag.data());
    if (ImGui::IsItemClicked() | ImGui::IsItemClicked(1))
    {
        m_SelectionContext = entity;
        PH_CORE_INFO("select entity {}", m_SelectionContext);
    }

    bool entityDeleted = false;
    if (ImGui::BeginPopupContextItem())
    {
        auto& name = m_scene->m_manager.get_component<NameComponent>(entity).name;

        if (ImGui::MenuItem("Delete Entity"))
            entityDeleted = true;

        if (ImGui::MenuItem("Add transform"))
        {
            m_scene->m_manager.add_component<TransformComponent>(entity);
            PH_CLIENT_INFO("Add transform component to {}", name);
        }

        if (ImGui::MenuItem("Add mesh"))
        {
            add_cube_mesh(entity);
            PH_CLIENT_INFO("Add mesh component to {}", name);
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
        m_scene->m_manager.destroy_entity(entity);
        if (m_SelectionContext == entity)
            m_SelectionContext = -1;
    }
}

void HierarchyPanel::add_cube_mesh(unsigned entity)
{
    static float vertices[24] = {// Coordinates for the vertices of a cube.
                                 1, 1, 1, 1, 1, -1, 1, -1, -1, 1, -1, 1, -1, 1, 1, -1, 1, -1, -1, -1, -1, -1, -1, 1};

    static float vertexColors[24] = {// An RGB color value for each vertex
                                     1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1};

    static int indices[24] = {// Vertex number for the six faces.
                              0, 1, 2, 3, 0, 3, 7, 4, 0, 4, 5, 1, 6, 2, 1, 5, 6, 5, 4, 7, 6, 7, 3, 2};

    MeshComponent &mesh_comp = m_scene->m_manager.add_component<MeshComponent>(entity);
    // create buffers / arrays glGenVertexArrays(1, &mesh_comp.vertex_array_object);
    glGenBuffers(1, &mesh_comp.vertex_buffer_object);
    glGenBuffers(1, &mesh_comp.element_buffer_object);

    glBindVertexArray(mesh_comp.vertex_array_object);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, mesh_comp.vertex_array_object);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2
    // array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_comp.element_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);

    glBindVertexArray(0);
}
} // namespace ph
