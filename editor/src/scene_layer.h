#ifndef EDITOR_SCENE_LAYER_H
#define EDITOR_SCENE_LAYER_H

#include <core/layer.h>
#include <scene/scene.h>
#include <renderer/frame_buffer.h>

PH_NAMESPACE_BEGIN

class SceneLayer : public Layer
{
public:
    SceneLayer(shared<Scene> frame);
    ~SceneLayer() = default;

    void on_update() override;
    void on_gui_render() override;
private:
    shared<ph::Scene> scene;
    shared<ph::Framebuffer> frame;
    shared<SceneRenderer> scene_renderer;
};

PH_NAMESPACE_END

#endif //EDITOR_SCENE_LAYER_H