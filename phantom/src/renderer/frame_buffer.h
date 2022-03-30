#pragma once

#include <glm/glm.hpp>

PH_NAMESPACE_BEGIN

struct FramebufferSpecification
{
	uint width = 0, height = 0;
	uint samples = 1;

	bool swap_chain_target = false;
};

class Framebuffer
{
public:
	virtual ~Framebuffer() = default;

	virtual void bind() = 0;
	virtual void unbind() = 0;

	virtual void resize(uint width, uint height) = 0;

	virtual uint get_color_attachment_renderer_id() const = 0;

	virtual const FramebufferSpecification& get_specification() const = 0;

	static shared<Framebuffer> create(const FramebufferSpecification& spec);
};

PH_NAMESPACE_END
