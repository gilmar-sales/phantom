#pragma once

#include <glbinding/gl/gl.h>
#include <glbinding/gl45core/gl.h>
#include <glbinding/gl45ext/gl.h>
#include <glbinding/glbinding.h>
#include <GLFW/glfw3.h>

#include <renderer/render_context.h>

PH_NAMESPACE_BEGIN

class OpenGLContext : public RenderContext
{
public:
	OpenGLContext(GLFWwindow* window_handle);

	virtual void init() override;
	virtual void swap_buffers() override;
private:
	GLFWwindow* m_window_handle;
};

PH_NAMESPACE_END
