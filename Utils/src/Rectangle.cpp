#include "Rectangle.h"

namespace nsfw::utils {

Rectangle::Rectangle(const Vector2f pos, const Vector2f size)
    : position(pos)
    , size(size)
{}

Rectangle::Rectangle(float posX, float posY, float sizeX, float sizeY)
    : position(posX, posY)
    , size(sizeX, sizeY)
{}

Rectangle::Rectangle()
    : position(0, 0)
    , size(0, 0)
{}

bool Rectangle::contains(const Vector2f &point) const {
    return (position.x < point.x && position.x+size.x > point.x
            && position.y < point.y && position.y+size.y > point.y);
}

bool Rectangle::contains(const Rectangle &rhs) const {
    // Если все грани другого прямоугольника лежат в пределах исходного
    return (position.x <= rhs.position.x && rhs.position.x < position.x+size.x &&
            position.x < rhs.position.x+rhs.size.x && rhs.position.x+rhs.size.x <= position.x+size.x &&
            position.y <= rhs.position.y && rhs.position.y < position.y+size.y &&
            position.y < rhs.position.y+rhs.size.y && rhs.position.y+rhs.size.y <= position.y+size.y);
}

bool Rectangle::overlaps(const Rectangle &rhs) const {
    // Если хотя-бы одна из вершин другого прямоугольника лежит внутри исходного
    return (position.x < rhs.position.x + rhs.size.x &&
            position.x + size.x > rhs.position.x &&
            position.y < rhs.position.y + rhs.size.y &&
            position.y + size.y > rhs.position.y);
}

}
