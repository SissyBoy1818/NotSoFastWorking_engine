#pragma once

#include <format>
#include "Event.h"
#include "Vector.h"

namespace nsfw::core {

class WindowCloseEvent final : public Event {
public:
    WindowCloseEvent() = default;

    EVENT_CLASS_TYPE(WindowClose)
};

class WindowResizedEvent final : public Event {
public:
    WindowResizedEvent(const utils::Vector2i windowSize) : m_windowSize(windowSize) {};

    [[nodiscard]] std::string toString() const override {
        return std::format("WindowResizedEvent: {}, {}", m_windowSize.x, m_windowSize.y);
    }

    EVENT_CLASS_TYPE(WindowResize)

private:
    utils::Vector2i m_windowSize;
};

}
