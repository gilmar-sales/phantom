#pragma once

#include "event.h"

PH_NAMESPACE_BEGIN

	class  KeyEvent : public Event {
	public:
		inline int get_key_code() { return m_keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
	protected:
		KeyEvent(int keycode)
			: m_keycode(keycode) {}

		int m_keycode;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int m_repeat_count)
			: KeyEvent(keycode), m_repeat_count(m_repeat_count) {}

		inline int GetRepeatCount() { return m_repeat_count; }

		std::string to_string() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keycode << "(" << m_repeat_count << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_repeat_count;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string to_string() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string to_string() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

PH_NAMESPACE_END
