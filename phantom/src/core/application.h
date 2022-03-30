#pragma once

#include <vector>

#include "window.h"
#include "layer_stack.h"
#include <gui/gui_layer.h>
#include <scene/scene.h>

PH_NAMESPACE_BEGIN

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

class Application
{
public:
    ~Application();

    static Application* get();

    void on_event(Event& event);

    std::string get_name() { return name; }

    static void push_layer(Layer* layer) { get()->impl_push_layer(layer); }
    static void push_overlay(Layer* layer) { get()->impl_push_overlay(layer); }
    static void run() { get()->impl_run(); }
    static shared<Window> get_window() { return get()->impl_get_window(); }

protected:
    Application(std::string name, uint width, uint height);

    void impl_push_layer(Layer* layer);
    void impl_push_overlay(Layer* layer);
    void impl_run();
    shared<Window> impl_get_window() { return windows[0]; };

    std::vector<shared<Window>> windows;
    LayerStack layer_stack;
    shared<Scene> scene;
    unique<GUILayer> gui_layer;

    std::string name;
    uint width;
    uint height;
};

PH_NAMESPACE_END
