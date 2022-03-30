#pragma once

#include "event.h"

PH_NAMESPACE_BEGIN

	class MouseMoveEvent : public Event {
	public:
		MouseMoveEvent(float x, float y)
			: mouseX(x), mouseY(y) {}

		inline float get_x() const { return this->mouseX; }
		inline float get_y() const { return this->mouseY; }

		std::string to_string() const override {
			std::stringstream ss;
			ss << "MouseMoveEvent: " << this->mouseX << ", " << this->mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float mouseX, mouseY;
	};

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float x_offset, float y_offset)
			: m_x_offset(x_offset), m_y_offset(y_offset) {}

		inline float get_x_ffset() const { return m_x_offset; }
		inline float get_y_ffset() const { return m_y_offset; }

		std::string to_string() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << get_x_ffset() << ", " << get_y_ffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_x_offset, m_y_offset;
	};

	class MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const { return m_button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button)
			: m_button(button) {}

		int m_button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string to_string() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string to_string() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

PH_NAMESPACE_END
