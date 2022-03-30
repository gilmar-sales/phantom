#pragma once

#include <memory>

#include <glm/glm.hpp>

PH_NAMESPACE_BEGIN

class Renderer;

class RendererAPI
{
	friend class Renderer;
public:
	enum class API
	{
		None = 0, OpenGL = 1
	};

	static void init()
	{
		get()->impl_init();
	}

	static void set_viewport(uint x, uint y, uint width, uint height)
	{
		get()->impl_set_viewport(x, y, width, height);
	};

	static void set_clear_color(const glm::vec4& color)
	{
		get()->impl_set_clear_color(color);
	};

	static void clear()
	{
		get()->impl_clear();
	}

	static void draw_indexed(
		const uint vertex_array_object,
		const uint vertex_buffer_object,
		const uint element_buffer_object, 
		uint index_count = 0)
	{
		get()->impl_draw_indexed(
		vertex_array_object,
		vertex_buffer_object,
		element_buffer_object, 
		index_count);
	}

protected:
	virtual void impl_init() = 0;
	virtual void impl_set_viewport(uint x, uint y, uint width, uint height) = 0;
	virtual void impl_set_clear_color(const glm::vec4& color) = 0;
	virtual void impl_clear() = 0;

	virtual void impl_draw_indexed(
		const uint vertex_array_object,
		const uint vertex_buffer_object,
		const uint element_buffer_object, 
		uint index_count = 0
	) = 0;

	static shared<RendererAPI> get() {
		static shared<RendererAPI> s_instance = create();
		return s_instance; 
	};
	static API get_api() { return s_api; }
	static shared<RendererAPI> create();
private:
	static API s_api;
};

PH_NAMESPACE_END
