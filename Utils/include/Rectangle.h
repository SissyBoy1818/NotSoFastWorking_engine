#pragma once

#include "Vector.h"

namespace nsfw::utils {

class Rectangle {
public:
    Rectangle(const Vector2f pos, const Vector2f size);
    Rectangle(float posX, float posY, float sizeX, float sizeY);
    Rectangle();

    [[nodiscard]] bool contains(const Vector2f &point) const;
    [[nodiscard]] bool contains(const Rectangle &rhs) const;
    [[nodiscard]] bool overlaps(const Rectangle &rhs) const;

public:
    Vector2f position;
    Vector2f size;
};

}

