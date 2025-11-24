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
        MousePressedEvent e(MOUSE_BUTTON_RIGHT, GetMousePosition());
        handler(e);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        MousePressedEvent e(MOUSE_BUTTON_LEFT, GetMousePosition());
        handler(e);
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
        MouseReleasedEvent e(MOUSE_BUTTON_RIGHT);
        handler(e);
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        MouseReleasedEvent e(MOUSE_BUTTON_LEFT);
        handler(e);
    }

    static utils::Vector2f lastMousePos = GetMousePosition();
    utils::Vector2f currentPos = GetMousePosition();
    if (currentPos.x != lastMousePos.x || currentPos.y != lastMousePos.y) {
        MouseMovedEvent e(currentPos);
        handler(e);
        lastMousePos = currentPos;
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
