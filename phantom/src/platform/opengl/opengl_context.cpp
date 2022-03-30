#include "opengl_context.h"

using namespace gl;

PH_NAMESPACE_BEGIN

OpenGLContext::OpenGLContext(GLFWwindow *window_handle) : m_window_handle(window_handle)
{
	if (!window_handle)
		Log::core_error("Window Handle is null!");
}

void OpenGLContext::init()
{
	glfwMakeContextCurrent(m_window_handle);
	glbinding::initialize(glfwGetProcAddress);

	if (glGetString(GL_VERSION) == nullptr)
		Log::core_error("Couldn't initialize OpenGL!");
	else
		Log::core_info("OpenGL initialized!");

	Log::core_info("OpenGL Info:");
	Log::core_info("  Vendor: {0}", glGetString(GL_VENDOR));
	Log::core_info("  Renderer: {0}", glGetString(GL_RENDERER));
	Log::core_info("  Version: {0}", glGetString(GL_VERSION));

	// if(!(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 1)))
	// 	Log::core_error( "Phantom requires at least OpenGL version 4.1!");
}

void OpenGLContext::swap_buffers()
{
	glfwSwapBuffers(m_window_handle);
}

PH_NAMESPACE_END
