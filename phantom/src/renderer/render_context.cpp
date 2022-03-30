#include "render_context.h"

#include "renderer.h"
#include <platform/opengl/opengl_context.h>

PH_NAMESPACE_BEGIN

unique<RenderContext> RenderContext::create(void* window)
{
	switch (Renderer::get_api())
	{
	case RendererAPI::API::None:    Log::core_error("RendererAPI::None is currently not supported!"); return nullptr;
	case RendererAPI::API::OpenGL:  return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window));
	}

	Log::core_error("Unknown RendererAPI!");
	return nullptr;
}

PH_NAMESPACE_END
