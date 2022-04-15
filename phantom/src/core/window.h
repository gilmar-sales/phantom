#pragma once

#include <glm/glm.hpp>

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <GLFW/glfw3.h>

#include <renderer/render_context.h>
#include <events/application_event.h>
#include <events/key_event.h>
#include <events/mouse_event.h>

PH_NAMESPACE_BEGIN

class Window
{
    using EventCallbackFn = std::function<void(Event &)>;

    struct WindowData
    {
        std::string title;
        uint width;
        uint height;
        std::vector<std::string> icons;
        glm::vec2 mouse_pos;
        bool maximized;
        EventCallbackFn event_callback;
    };

public:
    Window(std::string title, uint width, uint height, std::vector<std::string> icons);
    ~Window();

    void update();

    void close();

    bool should_close()
    {
        return glfwWindowShouldClose(native_window);
    }

    void *get_native_window() { return native_window; }
    uint get_width() { return data.width; }
    uint get_height() { return data.height; }
    glm::vec2 get_mouse_pos() { return data.mouse_pos; }
    bool is_maximized() { return data.maximized; }

    void set_event_callback(const EventCallbackFn &callback) { data.event_callback = callback; }
    void set_icon(std::vector<std::string> paths);

private:
    void init();

    static uint window_count;

    GLFWwindow *native_window;
    unique<RenderContext> context;
    WindowData data;
};

PH_NAMESPACE_END