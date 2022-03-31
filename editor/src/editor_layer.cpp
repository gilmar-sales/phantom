#include "editor_layer.h"
#include "BootstrapIconsFont.h"

#include <cmath>
#include <core/application.h>
#include <imgui.h>

#include <gui/extensions/extensions.h>
#include <gui/styles/styles.h>
#include <core/log.h>

namespace ph
{
    EditorLayer::EditorLayer() : Layer("EditorLayer")
    {
    }

    void EditorLayer::on_gui_render()
    {
        static ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiViewport *viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        static ImGuiIO &io = ImGui::GetIO();
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
        if (ImGui::Begin("DockSpace", nullptr, window_flags))
        {
            ImGui::PopStyleVar();
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
            {
                ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
            }

            draw_titlebar();

            draw_menubar();

            ImGui::Begin(ICON_BTSP_ARCHIVE" Resources");
            ImGui::End();

            ImGui::End(); // DockSpace
        }

        // m_hierarchy_panel->on_gui_render();
    }

    void EditorLayer::on_update()
    {
        // m_scene_frame->bind();

        // PH_CORE_INFO("Scene Frame");
    }

    float EditorLayer::draw_titlebar()
    {
        const float titlebar_height = 48.0f;
        const ImVec2 windowPadding = ImGui::GetCurrentWindow()->WindowPadding;

        return titlebar_height;
    }

    void EditorLayer::draw_menubar()
    {
        const float titlebar_height = 26.0f;
        static bool preferences_open = false;

        glm::vec2 pos = ph::Application::get_window()->get_mouse_pos();

        static glm::vec2 lastPos = pos;
        if (ImGui::IsMouseDown(0) && pos.y <= titlebar_height)
        {
            static double moveOffsetX = 0;
            static double moveOffsetY = 0;

            // Calculate the difference between the cursor pos and window pos
            moveOffsetX = pos.x - lastPos.x;
            moveOffsetY = pos.y - lastPos.y;

            int xpos, ypos;
            GLFWwindow *window = (GLFWwindow *)ph::Application::get_window()->get_native_window();
            glfwGetWindowPos(window, &xpos, &ypos);

            glfwSetWindowPos(window, floor(xpos) + moveOffsetX, floor(ypos) + moveOffsetY);
        }

        lastPos = pos;

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem(ICON_BTSP_FOLDERPLUS " New Project...", "Ctrl+N"))
                { /* Do stuff */
                }
                ImGui::Separator();
                if (ImGui::MenuItem(ICON_BTSP_FOLDEROPEN " Open Project...", "Ctrl+O"))
                { /* Do stuff */
                }
                if (ImGui::MenuItem(ICON_BTSP_FOLDER " Open Recent"))
                { /* Do stuff */
                }
                ImGui::Separator();
                if (ImGui::MenuItem(ICON_BTSP_FOLDERSYMLINK " Save", "Ctrl+S"))
                { /* Do stuff */
                }
                if (ImGui::MenuItem(ICON_BTSP_FOLDERSYMLINK " Save As...", "Ctrl+Shift+S"))
                { /* Do stuff */
                }
                ImGui::Separator();
                if (ImGui::MenuItem(ICON_BTSP_FOLDERDASH " Close Project", "Ctrl+W"))
                {
                }
                if (ImGui::MenuItem(ICON_BTSP_SHUTDOWN " Close Phantom", "Alt+F4"))
                {
                    Application::get_window()->close();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo...", "Ctrl+N"))
                { /* Do stuff */
                }
                if (ImGui::MenuItem("Redo...", "Ctrl+O"))
                { /* Do stuff */
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "Ctrl+X"))
                { /* Do stuff */
                }
                if (ImGui::MenuItem("Copy", "Ctrl+C"))
                { /* Do stuff */
                }
                if (ImGui::MenuItem("Paste", "Ctrl+V"))
                { /* Do stuff */
                }
                ImGui::Separator();
                if (ImGui::MenuItem(ICON_BTSP_GEAR " Preferences...", "Ctrl+,"))
                {
                    preferences_open = true;
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Entity"))
            {
                if (ImGui::MenuItem("Create Empty"))
                { /* Do stuff */
                }
                if (ImGui::BeginMenu("Create Geometry"))
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

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Component"))
            {
                if (ImGui::BeginMenu("Enable Component"))
                {
                    if (ImGui::MenuItem("Camera"))
                    { /* Do stuff */
                    }
                    if (ImGui::MenuItem("Transform"))
                    { /* Do stuff */
                    }
                    if (ImGui::MenuItem("RigidBody"))
                    { /* Do stuff */
                    }
                    ImGui::EndMenu();
                }

                ImGui::EndMenu();
            }

            ImGui::SetCursorPosX(ImGui::GetWindowContentRegionMax().x * 0.5f - 150);

            ImGui::Text(ICON_BTSP_ACTIVITY " %s - %.3f ms/frame (%.1f FPS)", ph::Application::get()->get_name().c_str(), 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);


            ImGui::EndMenuBar();
        }

        if (preferences_open)
        {

            ImGui::Begin("Preferences ", &preferences_open,
                         ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);

            static int style_idx = 0;
            if (ImGui::Combo("Theme", &style_idx, "PhantomDark\0PhantomLight\0Dark\0Light\0Classic\0"))
            {
                switch (style_idx)
                {
                    case 0: StylePhantomDark(); break;
                    case 1: StylePhantomLight(); break;
                    case 2: ImGui::StyleColorsDark(); break;
                    case 3: ImGui::StyleColorsLight(); break;
                    case 4: ImGui::StyleColorsClassic(); break;
                }
            }

            ImGui::End();
        }
    }

} // namespace ph