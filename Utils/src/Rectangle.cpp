#include "Rectangle.h"

namespace nsfw::utils {

Rectangle::Rectangle(const Vector2f pos, const Vector2f size)
    : m_position(pos)
    , m_size(size)
{}

bool Rectangle::contains(const Vector2f &point) const {
    return (m_position.x < point.x && m_position.x+m_size.x > point.x
            && m_position.y < point.y && m_position.y+m_size.y > point.y);
}

bool Rectangle::contains(const Rectangle &rhs) const {
    // Если исходный прямоугольник меньше, то он не может содержать другой
    if (m_size.x < rhs.m_size.x || m_size.y < rhs.m_size.y)
        return false;
    // Если какая-то из граней другого прямоугольника не лежит в пределах исходного
    if (m_position.x > rhs.m_position.x ||
        m_position.x+m_size.x < rhs.m_position.x+rhs.m_size.x ||
        m_position.y > rhs.m_position.y ||
        m_position.y+m_size.y < rhs.m_position.y+rhs.m_size.y)
        return false;

    // Иначе
    return true;
}

bool Rectangle::overlaps(const Rectangle &rhs) const {
    // Если хотя-бы одна из вершин другого прямоугольника лежит внутри исходного
    return (contains(rhs.m_position) ||
        contains(rhs.m_position+rhs.m_size) ||
        contains({rhs.m_position.x, rhs.m_position.y+rhs.m_size.y}) ||
        contains({rhs.m_position.x+rhs.m_size.x, rhs.m_position.y}));
}

}
