#pragma once

#include <glbinding/gl/gl.h>
#include <glbinding/gl45core/gl.h>
#include <glbinding/gl45ext/gl.h>
#include <glbinding/glbinding.h>

#include <renderer/renderer_api.h>

PH_NAMESPACE_BEGIN

class OpenGLRendererAPI : public RendererAPI
{
public:
	OpenGLRendererAPI() = default;

	virtual void impl_init() override;
	virtual void impl_set_viewport(uint x, uint y, uint width, uint height) override;

	virtual void impl_set_clear_color(const glm::vec4& color) override;
	virtual void impl_clear() override;

	virtual void impl_draw_indexed(
		const uint vertex_array_object,
		const uint vertex_buffer_object,
		const uint element_buffer_object,
		uint index_count = 0
	) override;
};

PH_NAMESPACE_END
