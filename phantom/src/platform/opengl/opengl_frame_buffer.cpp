#include "opengl_frame_buffer.h"

using namespace gl;

PH_NAMESPACE_BEGIN

static const uint s_max_framebuffer_size = 8192u;

OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
	: m_specification(spec)
{
	invalidate();
}

OpenGLFramebuffer::~OpenGLFramebuffer()
{
	glDeleteFramebuffers(1, &m_renderer_id);
	glDeleteTextures(1, &m_color_attachment);
	glDeleteTextures(1, &m_depth_attachment);
}

void OpenGLFramebuffer::invalidate()
{
	if (m_renderer_id)
	{
		glDeleteFramebuffers(1, &m_renderer_id);
		glDeleteTextures(1, &m_color_attachment);
		glDeleteTextures(1, &m_depth_attachment);
	}

	glCreateFramebuffers(1, &m_renderer_id);
	glBindFramebuffer(GL_FRAMEBUFFER, m_renderer_id);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_color_attachment);
	glBindTexture(GL_TEXTURE_2D, m_color_attachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_specification.width, m_specification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_attachment, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_depth_attachment);
	glBindTexture(GL_TEXTURE_2D, m_depth_attachment);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_specification.width, m_specification.height);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth_attachment, 0);

	if (!(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE))
		Log::core_error( "Framebuffer is incomplete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFramebuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_renderer_id);
	glViewport(0, 0, m_specification.width, m_specification.height);
}

void OpenGLFramebuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFramebuffer::resize(uint width, uint height)
{
	if (width == m_specification.width && height == m_specification.height)
	{
		// Log::core_warning("Attempted to rezize framebuffer with same dimensions");
		return;
	}

	if (width == 0 || height == 0 || width > s_max_framebuffer_size || height > s_max_framebuffer_size)
	{
		Log::core_warning("Attempted to rezize framebuffer to {0}, {1}", width, height);
		return;
	}
	m_specification.width = width;
	m_specification.height = height;

	invalidate();
}

PH_NAMESPACE_END
