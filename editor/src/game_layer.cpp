#include "game_layer.h"
#include <imgui.h>
#include <renderer/frame_buffer.h>

#include "BootstrapIconsFont.h"

PH_NAMESPACE_BEGIN

GameLayer::GameLayer(shared<Scene> scene) : scene(scene)
{
    ph::FramebufferSpecification spec = {100, 100, 2, true};
    frame = Framebuffer::create(spec);
    scene_renderer = std::make_shared<SceneRenderer>(frame);
}

void GameLayer::on_update()
{
    scene->on_editor_render(scene_renderer, 0.16);
}

void GameLayer::on_gui_render()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
    ImGui::Begin(ICON_BTSP_CONTROLLER " Game");
    ImVec2 avail_size = ImGui::GetContentRegionAvail();
    frame->resize(avail_size.x, avail_size.y);
    frame->bind();
    glClear(GL_COLOR_BUFFER_BIT);
    frame->unbind();
    ImGui::Image((void *)(intptr_t)frame->get_color_attachment_renderer_id(), avail_size);
    ImGui::End();
    ImGui::PopStyleVar();
}

PH_NAMESPACE_END
