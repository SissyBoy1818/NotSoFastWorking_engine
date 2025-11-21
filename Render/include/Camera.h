#pragma once

#include "raylib.h"
#include "Rectangle.h"

namespace nsfw::render {
/**
 * \class Camera
 * \brief Камера для управления видимой областью и преобразования координат между мировым и экранным пространством
 */
class Camera {
public:
    /**
     * \brief Конструктор класса
     * \param rect Прямоугольная область, задающая позицию и область видимости камеры
     */
    explicit Camera(const utils::Rectangle &rect);

    /**
     * \brief Конструктор класса
     * \param position Позиция камеры
     * \param area Область видимости камеры
     */
    Camera(utils::Vector2f position, utils::Vector2f area);

    /**
     * \brief Оператор для приведения камеры к типу, используемому в raylib
     */
    explicit operator Camera2D() const;

};

}
