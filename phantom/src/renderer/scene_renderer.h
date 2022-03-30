#pragma once

#include <renderer/frame_buffer.h>

PH_NAMESPACE_BEGIN

class SceneRenderer
{
public:
    SceneRenderer(shared<Framebuffer> frame): frame(frame) {};
    ~SceneRenderer() {};
    
private:
    shared<Framebuffer> frame;
};


PH_NAMESPACE_END
