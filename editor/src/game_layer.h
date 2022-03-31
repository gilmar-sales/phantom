#ifndef EDITOR_GAME_LAYER_H
#define EDITOR_GAME_LAYER_H

#include <core/layer.h>
#include <scene/scene.h>
#include <renderer/frame_buffer.h>

PH_NAMESPACE_BEGIN

class GameLayer : public Layer
{
public:
    GameLayer(shared<Scene> frame);
    ~GameLayer() = default;

    void on_update() override;
    void on_gui_render() override;
private:
    shared<Scene> scene;
    shared<Framebuffer> frame;
    shared<SceneRenderer> scene_renderer;
};

PH_NAMESPACE_END

#endif //EDITOR_GAME_LAYER_H
