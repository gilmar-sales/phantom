#include "renderer_api.h"

#include <platform/opengl/opengl_renderer_api.h>

PH_NAMESPACE_BEGIN

RendererAPI::API RendererAPI::s_api = RendererAPI::API::OpenGL;

shared<RendererAPI> RendererAPI::create()
{
	switch (s_api)
	{
	case RendererAPI::API::None:    Log::core_error("RendererAPI::None is currently not supported!"); return nullptr;
	case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLRendererAPI>();
	}

	Log::core_error("Unknown RendererAPI!");
	return nullptr;
}

PH_NAMESPACE_END