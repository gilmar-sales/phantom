#include "frame_buffer.h"

#include <renderer/renderer.h>

#include <platform/opengl/opengl_frame_buffer.h>

PH_NAMESPACE_BEGIN

shared<Framebuffer> Framebuffer::create(const FramebufferSpecification& spec)
{
	switch (Renderer::get_api())
	{
	case RendererAPI::API::None:    Log::core_error("RendererAPI::None is currently not supported!"); return nullptr;
	case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLFramebuffer>(spec);
	default: Log::core_error("Unknown RendererAPI!");
	}

	return nullptr;
}

PH_NAMESPACE_END
