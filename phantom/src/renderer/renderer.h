#pragma once

#include "renderer_api.h"

PH_NAMESPACE_BEGIN

class Renderer
{
public:
	static void init();
	static void shutdown();

	static void on_window_resize(uint width, uint height);

	static RendererAPI::API get_api() { return RendererAPI::get_api(); }
};

PH_NAMESPACE_END
