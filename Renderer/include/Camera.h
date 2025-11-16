#pragma once

#include "raylib.h"
#include "Rectangle.h"
#include "GameObject.h"

namespace nsfw::render {
/**
 * \class Camera
 * \brief Камера для управления видимой областью и преобразования координат между мировым и экранным пространством
 */
class Camera : public ecs::GameObject {
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
     * \brief Преобразовать координаты камеры в мировые
     * \param point Позиция (пиксель) на экране
     * \return Позиция в мировых координатах с учетом смещения камеры
     */
    [[nodiscard]] utils::Vector2f CameraToWorldPosition(utils::Vector2i point) const;

    /**
     * \brief Преобразовать мировые координаты в координаты камеры
     * \param point Позиция в мировых координатах
     * \return Позиция (пиксель) на экране
     */
    [[nodiscard]] utils::Vector2i WorldToCameraPosition(utils::Vector2f point) const;

    /**
     * \brief Изменить область видимости камеры в factor раз
     * \param factor Коэффициент изменения
     */
    void zoom(float factor);

    /**
     * \brief Оператор для приведения камеры к типу, используемому в raylib
     */
    explicit operator Camera2D() const;

};

}
