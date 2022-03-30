#pragma once

#include "event.h"

PH_NAMESPACE_BEGIN

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(unsigned width, unsigned height)
		: m_width(width), m_height(height) {}

	inline unsigned get_width() const { return m_width; }
	inline unsigned get_height() const { return m_height; }

	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << get_width() << ", " << get_height();
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowResize)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)

private:
	unsigned m_width, m_height;
};

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() {}

	EVENT_CLASS_TYPE(WindowClose)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppTickEvent : public Event
{
public:
	AppTickEvent() {}

	EVENT_CLASS_TYPE(AppTick)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppUpdateEvent : public Event
{
	AppUpdateEvent() {}

	EVENT_CLASS_TYPE(AppUpdate)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

PH_NAMESPACE_END