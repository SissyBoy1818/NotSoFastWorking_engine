#pragma once

#include "Vector.hpp"

namespace nsfw::utils {

class Rectangle {
public:
    Rectangle(const Vector2f pos, const Vector2f size);

    [[nodiscard]] bool contains(const Vector2f &point) const;
    [[nodiscard]] bool contains(const Rectangle &rhs) const;
    [[nodiscard]] bool overlaps(const Rectangle &rhs) const;

public:
    Vector2f m_position;
    Vector2f m_size;
};

}

