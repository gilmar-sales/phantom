#include "window.h"
#include <cmath>
#include <renderer/renderer_api.h>

PH_NAMESPACE_BEGIN

uint Window::window_count = 0;

static void glfw_error_callback(int error, const char *description)
{
    Log::core_error("[glfw] ({0}): {1}", error, description);
}

Window::Window(std::string title, uint width, uint height) : data({title, width, height, {}, false})
{
    init();
}

Window::~Window()
{
    glfwDestroyWindow(native_window);

    glfwTerminate();
}

void Window::update()
{
    context->swap_buffers();

//    glfwWaitEvents();
     glfwPollEvents();
}

void Window::close()
{
    glfwSetWindowShouldClose(native_window, 1);
    glfwPostEmptyEvent();
}

void Window::init()
{
    if (!window_count)
    {
        if (!glfwInit())
            Log::core_error("Couldn't initialize GLFW!");
        else
            Log::core_info("Creating window {} {} {}", data.title, data.width, data.height);

        glfwSetErrorCallback(glfw_error_callback);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    window_count++;

    //glfwWindowHint(GLFW_DECORATED, false);
    glfwWindowHint(GLFW_MAXIMIZED, data.maximized);

    native_window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);

    context = RenderContext::create(native_window);
    context->init();

    glfwSetWindowUserPointer(native_window, &data);
    glfwSwapInterval(0);

    RendererAPI::set_clear_color({0.2f, 0.4f, 0.6f, 0.8f});

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(native_window, [](GLFWwindow *window, int width, int height)
                              {
                                  WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                                  data.width = width;
                                  data.height = height;

                                  WindowResizeEvent event(width, height);
                                  data.event_callback(event); });

    glfwSetWindowCloseCallback(native_window, [](GLFWwindow *window)
                               {
                                   WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                                   WindowCloseEvent event;
                                   data.event_callback(event); });

    glfwSetKeyCallback(native_window, [](GLFWwindow *window, int key, int scancode, int action, int modes)
                       {
                           WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

                           switch (action)
                           {
                           case GLFW_PRESS:
                           {
                               KeyPressedEvent event(key, 0);
                               data.event_callback(event);
                               break;
                           }
                           case GLFW_RELEASE:
                           {
                               KeyReleasedEvent event(key);
                               data.event_callback(event);
                               break;
                           }
                           case GLFW_REPEAT:
                           {
                               KeyPressedEvent event(key, 1);
                               break;
                           }
                           } });

    glfwSetCharCallback(native_window, [](GLFWwindow *window, unsigned int key)
                        {
                            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

                            KeyTypedEvent event(key);
                            data.event_callback(event); });

    glfwSetMouseButtonCallback(native_window, [](GLFWwindow *window, int button, int action, int mods)
                               {
                                   WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

                                   switch (action)
                                   {
                                   case GLFW_PRESS:
                                   {
                                       MouseButtonPressedEvent event(button);
                                       data.event_callback(event);
                                       break;
                                   }
                                   case GLFW_RELEASE:
                                   {
                                       MouseButtonReleasedEvent event(button);
                                       data.event_callback(event);
                                       break;
                                   }
                                   } });

    glfwSetScrollCallback(native_window, [](GLFWwindow *window, double xOffset, double yOffset)
                          {
                              WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

                              MouseScrolledEvent event((float)xOffset, (float)yOffset);
                              data.event_callback(event); });

    glfwSetCursorPosCallback(native_window, [](GLFWwindow *window, double x, double y)
                             {
                                 WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

                                 float fx = floor(x);
                                 float fy = floor(y);
                                 MouseMoveEvent event(fx, fy);
                                 data.event_callback(event);
                                 data.mouse_pos = {fx, fy}; });

    glfwSetWindowMaximizeCallback(native_window, [](GLFWwindow *window, int maximized)
                                  {
                                      WindowData *data = (WindowData *)glfwGetWindowUserPointer(window);

                                      data->maximized = maximized; });
}

PH_NAMESPACE_END
