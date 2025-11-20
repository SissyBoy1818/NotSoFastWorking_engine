#pragma once

#include "Rectangle.h"
#include "raylib.h"

namespace nsfw::ecs {

using Entity = uint32_t;

struct BaseComponent {
    Entity owner;

    bool operator<(const BaseComponent &rhs) const {
        return owner < rhs.owner;
    }
    bool operator==(const BaseComponent &rhs) const {
        return owner == rhs.owner;
    }
};

struct Transform : BaseComponent {
    utils::Rectangle rectangle;
    utils::Vector2f scale = {1.0f, 1.0f};
    float rotation = 0;
};

struct PanningCamera : BaseComponent{
    utils::Vector2f pannedPosition; ///< "Закрепленная" позиция в координатах экрана
    bool isPanned = false; ///< Зажата ли ЛКМ
};

struct Drawable : BaseComponent {
    Texture2D texture;
};

}
