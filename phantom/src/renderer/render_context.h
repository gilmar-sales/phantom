#pragma once

PH_NAMESPACE_BEGIN

class RenderContext
{
public:
	virtual ~RenderContext() = default;

	virtual void init() = 0;
	virtual void swap_buffers() = 0;

	static unique<RenderContext> create(void* window);
};

PH_NAMESPACE_END