#include "scene_layer.h"
#include <imgui.h>
#include <renderer/frame_buffer.h>

#include "BootstrapIconsFont.h"

PH_NAMESPACE_BEGIN

SceneLayer::SceneLayer(shared<Scene> scene) : scene(scene)
{
    ph::FramebufferSpecification spec = {100, 100, 2, true};
    frame = Framebuffer::create(spec);
    scene_renderer = std::make_shared<SceneRenderer>(frame);
}

void SceneLayer::on_update()
{
    scene->on_editor_render(scene_renderer, 0.16);
}

void SceneLayer::on_gui_render()
{
    ImGui::Begin(ICON_BTSP_CAMERAREELS " Scene");
    ImVec2 avail_size = ImGui::GetContentRegionAvail();
    frame->resize(avail_size.x, avail_size.y);
    frame->unbind();
    ImGui::Image((void *)(intptr_t)frame->get_color_attachment_renderer_id(), avail_size);
    ImGui::End();
}

PH_NAMESPACE_END
