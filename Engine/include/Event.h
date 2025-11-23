#pragma once

#include <string>
#include <functional>

namespace nsfw::core {

enum class EventType {
    None = 0,
    WindowClose, WindowResize,
    MouseButtonPressed, MouseButtonReleased,
    MouseMoved, MouseScrolled,
    KeyPressed, KeyReleased
};

#define EVENT_CLASS_TYPE(type)  static EventType getStaticType() { return EventType::type; }\
                                virtual EventType getEventType() const override { return getStaticType(); }\
                                virtual const char* getName() const override { return #type; }

class Event {
public:
    virtual ~Event() = default;
    [[nodiscard]] virtual EventType getEventType() const = 0;
    [[nodiscard]] virtual const char * getName() const = 0;
    [[nodiscard]] virtual std::string toString() const { return getName(); };

    bool handled = false;
};

class EventDispatcher {
private:
    template <typename T>
    using EventFn = std::function<bool(T&)>;

    Event& m_event;

public:
    EventDispatcher(Event &event) : m_event(event) {}

    template <typename T>
    bool dispatch(EventFn<T> func) {
        if (m_event.getEventType() == T::getStaticType() && !m_event.handled) {
            m_event.handled = func(*static_cast<T *>(&m_event));
            return true;
        }

        return false;
    }

private:
    template <typename T>
    using EventFn = std::function<bool(T&)>;

};

}