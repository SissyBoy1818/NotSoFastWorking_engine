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
    // Если исходный прямоугольник меньше, то он не может содержать другой
    if (size.x < rhs.size.x || size.y < rhs.size.y)
        return false;
    // Если какая-то из граней другого прямоугольника не лежит в пределах исходного
    if (position.x > rhs.position.x ||
        position.x+size.x < rhs.position.x+rhs.size.x ||
        position.y > rhs.position.y ||
        position.y+size.y < rhs.position.y+rhs.size.y)
        return false;

    // Иначе
    return true;
}

bool Rectangle::overlaps(const Rectangle &rhs) const {
    // Если хотя-бы одна из вершин другого прямоугольника лежит внутри исходного
    return (contains(rhs.position) ||
        contains(rhs.position+rhs.size) ||
        contains({rhs.position.x, rhs.position.y+rhs.size.y}) ||
        contains({rhs.position.x+rhs.size.x, rhs.position.y}));
}

}
