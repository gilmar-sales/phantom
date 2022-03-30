#pragma once

#include <core/layer.h>
#include <core/window.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

PH_NAMESPACE_BEGIN

class GUILayer : public Layer
{
private:
    bool m_block_events = true;
    float m_time = 0.9f;
    shared<Window> window;
public:
    GUILayer(shared<Window> window);
    ~GUILayer() = default;

    virtual void on_attach() override;
    virtual void on_detach() override;
    virtual void on_event(Event& event) override;

    void begin();
    void end();

    void block_events(bool block) { m_block_events = block; }
};

PH_NAMESPACE_END
