#include <phantom.h>

#include "BootstrapIconsFont.h"
#include "editor_layer.h"
#include "scene_layer.h"
#include "hierarchy_layer.h"

#include <renderer/frame_buffer.h>

class EditorApp : public ph::Application
{
  public:
    EditorApp() : ph::Application("Phantom Editor", 1280, 720)
    {
      ImGuiIO& io = ImGui::GetIO();
      io.Fonts->AddFontFromFileTTF("resources/OpenSans.ttf", 16);

      static const ImWchar icons_ranges[] = { ICON_MIN_BTSP, ICON_MAX_BTSP, 0 };
      ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
      io.Fonts->AddFontFromFileTTF("resources/BootstrapIconsFont.ttf", 16, &icons_config, icons_ranges );

      impl_push_layer(new ph::EditorLayer());

      impl_push_layer(new ph::SceneLayer(scene));
      impl_push_layer(new ph::HierarchyLayer(scene));
    };
    ~EditorApp() = default;

    void on_event(ph::Event &e){};
    void on_update()
    {
    }

  private:
  shared<ph::Framebuffer> scene_frame;
};

PH_SET_APPLICATION(EditorApp)