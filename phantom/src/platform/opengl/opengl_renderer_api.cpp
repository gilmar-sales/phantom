#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "opengl_renderer_api.h"

using namespace gl;

PH_NAMESPACE_BEGIN

void OpenGLRendererAPI::impl_init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
}

void OpenGLRendererAPI::impl_set_viewport(uint x, uint y, uint width, uint height)
{
	glViewport(x, y, width, height);
}

void OpenGLRendererAPI::impl_set_clear_color(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::impl_clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::impl_draw_indexed(
	const uint vertex_array_object,
	const uint vertex_buffer_object,
	const uint element_buffer_object,
	uint index_count
)
{
	//glBindVertexArray(vertex_array_object);
	//glBindVertexBuffer(vertex_buffer_object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);

	glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
}

PH_NAMESPACE_END
