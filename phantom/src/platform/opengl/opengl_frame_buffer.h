#pragma once

#include <glbinding/gl/gl.h>
#include <glbinding/gl45core/gl.h>
#include <glbinding/gl45ext/gl.h>
#include <glbinding/glbinding.h>

#include <renderer/frame_buffer.h>

PH_NAMESPACE_BEGIN

class OpenGLFramebuffer : public Framebuffer
{
public:
	OpenGLFramebuffer(const FramebufferSpecification& spec);
	virtual ~OpenGLFramebuffer();

	void invalidate();

	virtual void bind() override;
	virtual void unbind() override;

	virtual void resize(uint width, uint height) override;

	virtual uint get_color_attachment_renderer_id() const override { return m_color_attachment; }

	virtual const FramebufferSpecification& get_specification() const override { return m_specification; }
private:
	uint m_renderer_id = 0;
	uint m_color_attachment = 0;
	uint m_depth_attachment = 0;
	FramebufferSpecification m_specification;
};

PH_NAMESPACE_END
