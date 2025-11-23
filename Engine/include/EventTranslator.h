#pragma once

#include "raylib.h"
#include "InputEvents.h"
#include "WindowEvents.h"

namespace nsfw::core {

class EventTranslator {
public:
    template <typename HandlerFn>
    static void checkEvents(HandlerFn handler);
};

// Реализация

template<typename HandlerFn>
void EventTranslator::checkEvents(HandlerFn handler) {
    if (IsWindowResized()) {
        WindowResizedEvent e({GetScreenWidth(), GetScreenHeight()});
        handler(e);
    }

    if (WindowShouldClose()) {
        WindowCloseEvent e;
        handler(e);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        MousePressedEvent e(MOUSE_BUTTON_RIGHT);
        handler(e);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        MousePressedEvent e(MOUSE_BUTTON_LEFT);
        handler(e);
    }

    if (GetMouseDelta().x != 0 || GetMouseDelta().y != 0) {
        MouseMovedEvent e(GetMouseDelta());
        handler(e);
    }

    if (GetMouseWheelMove() != 0) {
        MouseScrolledEvent e(GetMouseWheelMove());
        handler(e);
    }

    if (GetKeyPressed() != 0) {
        KeyPressedEvent e(GetKeyPressed());
        handler(e);
    }

    for (int key = KEY_NULL; key <= KEY_KB_MENU; key++) {
        if (IsKeyReleased(key)) {
            KeyReleasedEvent e(key);
            handler(e);
        }
    }
}

}
