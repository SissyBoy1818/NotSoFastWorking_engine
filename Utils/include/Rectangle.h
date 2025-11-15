#pragma once

#include "Vector.h"

namespace nsfw::utils {

/**
 * \class Rectangle
 * \brief Класс прямоугольной области
 */
class Rectangle {
public:
    Rectangle(const Vector2f pos, const Vector2f size);
    Rectangle(float posX, float posY, float sizeX, float sizeY);
    Rectangle();

    /**
     * \brief Проверяет, находится ли заданная точка внутри области прямоугольника
     * \param point Вектор координат точки
     * \return True - если точка находится внутри прямоугольника, иначе - else
     */
    [[nodiscard]] bool contains(const Vector2f &point) const;

    /**
     * \brief Проверяет, находится ли заданный прямоугольник внутри исходного
     * \param rhs Другой прямоугольник
     * \return True - если rhs находится внутри прямоугольника, иначе - else
     */
    [[nodiscard]] bool contains(const Rectangle &rhs) const;

    /**
     * \brief Проверяет, пересекается ли заданный прямоугольник с этим
     * \param rhs Другой прямоугольник
     * \return True - если rhs пересекается с исходным прямоугольником, иначе - else
     */
    [[nodiscard]] bool overlaps(const Rectangle &rhs) const;

public:
    Vector2f position; ///< Вектор координат прямоугольника
    Vector2f size; ///< Размеры прямоугольника
};

}

