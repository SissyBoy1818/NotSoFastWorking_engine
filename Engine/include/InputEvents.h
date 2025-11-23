#pragma once

#include <format>
#include "Event.h"
#include "Vector.h"

namespace nsfw::core {

class MousePressedEvent final : public Event {
public:
    explicit MousePressedEvent(const int button) : m_mouseButton(button) {};

    [[nodiscard]] int getMouseButton() const { return m_mouseButton; };

    [[nodiscard]] std::string toString() const override { return std::format("MousePressedEvent: {}", m_mouseButton); }

    EVENT_CLASS_TYPE(MouseButtonPressed)

private:
    int m_mouseButton;
};

class MouseReleasedEvent final : public Event {
public:
    explicit MouseReleasedEvent(const int button) : m_mouseButton(button) {};

    [[nodiscard]] int getMouseButton() const { return m_mouseButton; };

    [[nodiscard]] std::string toString() const override { return std::format("MouseReleasedEvent: {}", m_mouseButton); }

    EVENT_CLASS_TYPE(MouseButtonReleased)

private:
    int m_mouseButton;
};

class MouseMovedEvent final : public Event {
public:
    MouseMovedEvent(const utils::Vector2f mousePos) : m_mousePosition(mousePos) {};

    [[nodiscard]] utils::Vector2f getMousePosition() const { return m_mousePosition; }

    [[nodiscard]] std::string toString() const override {
        return std::format("MouseMovedEvent: {}, {}", m_mousePosition.x, m_mousePosition.y);
    };

    EVENT_CLASS_TYPE(MouseMoved)

private:
    utils::Vector2f m_mousePosition;
};

class MouseScrolledEvent final : public Event {
public:
    MouseScrolledEvent(float scroll) : m_scroll(scroll) {};

    [[nodiscard]] std::string toString() const override {
        return std::format("MouseScrolledEvent: {}", m_scroll);
    }

    EVENT_CLASS_TYPE(MouseScrolled)

private:
    float m_scroll;
};

class KeyPressedEvent final : public Event {
public:
    KeyPressedEvent(int key) : m_key(key) {};

    [[nodiscard]] std::string toString() const override {
        return std::format("KeyPressedEvent: {}", m_key);
    }

    EVENT_CLASS_TYPE(KeyPressed)

private:
    int m_key;
};

class KeyReleasedEvent final : public Event {
public:
    KeyReleasedEvent(int key) : m_key(key) {};

    [[nodiscard]] std::string toString() const override {
        return std::format("KeyReleasedEvent: {}", m_key);
    }

    EVENT_CLASS_TYPE(KeyReleased)

private:
    int m_key;
};

}
