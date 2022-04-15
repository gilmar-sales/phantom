#include "application.h"

#include <renderer/renderer_api.h>

PH_NAMESPACE_BEGIN

Application:: Application(std::string name, uint width, uint height, std::vector<std::string> icons):
name(name),
width(width),
height(height),
icons(icons),
windows(0) 
{
    windows.push_back(std::make_shared<Window>(name, width, height, icons));

    windows[0]->set_event_callback(BIND_EVENT_FN(on_event));

    scene = std::make_shared<Scene>();
    layer_stack = LayerStack();

    gui_layer = std::make_unique<GUILayer>(windows[0]);
    gui_layer->on_attach();
};

Application::~Application()
 {
    for(Layer* layer : layer_stack)
    {
        layer->on_detach();
    }

    gui_layer->on_detach();
};

void Application::on_event(Event& event) 
{
    // Log::core_trace("[event]: {}", event.to_string());
}

void Application::impl_push_layer(Layer* layer) {
    layer_stack.push_layer(layer);
    layer->on_attach();
}

void Application::impl_push_overlay(Layer* layer) {
    layer_stack.push_overlay(layer);
    layer->on_attach();
}

void Application::impl_run()
{
    

    while(!windows[0]->should_close())
    {
        RendererAPI::clear();
        
        // scene.update();

        for(Layer* layer : layer_stack)
        {
            layer->on_update();
        }

        gui_layer->begin();
            for(Layer* layer : layer_stack)
            {
                layer->on_gui_render();
            }
            gui_layer->on_gui_render();
        gui_layer->end();
        
        windows[0]->update();
    }
}

PH_NAMESPACE_END