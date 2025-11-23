#pragma once

#include "Rectangle.h"

namespace nsfw::ecs {

using TextureID = uint32_t;
using Entity = uint32_t;

struct Transform {
    utils::Rectangle rectangle;
    float scale = 1.0f;
    float rotation = 0;
};

struct PanningCamera {
    utils::Vector2f pannedPosition; ///< "Закрепленная" позиция в координатах экрана
    bool isPanned = false; ///< Зажата ли ЛКМ
};

struct ZoomableCamera {
    float minZoom;
    float maxZoom;

    float delta;
};

struct Drawable {
    TextureID texture;
};

}

namespace nsfw::render {

/**
 * \brief Преобразовать координаты камеры в мировые
 * \param cameraTransform Компонент Transform камеры, от-но которой вычисляются смещения
 * \param point Позиция в координатах камеры
 * \return Позиция в мире
 */
inline utils::Vector2f CameraToWorldPosition(const ecs::Transform &cameraTransform,
                                             const utils::Vector2f point) {
    const auto position = cameraTransform.rectangle.position;
    const auto scale = cameraTransform.scale;

    return {static_cast<float>(point.x) / scale + position.x,
            static_cast<float>(point.y) / scale + position.y};
}

/**
 * \brief Преобразовать мировые координаты в координаты камеры
 * \param cameraTransform Компонент Transform камеры, от-но которой вычисляются смещения
 * \param point Позиция в мировых координатах
 * \return Позиция на экране
 */
inline utils::Vector2f WorldToCameraPosition(const ecs::Transform &cameraTransform,
                                             const utils::Vector2f point) {
    const auto position = cameraTransform.rectangle.position;
    const auto scale = cameraTransform.scale;

    return {(point.x - position.x) * scale,
            (point.y - position.y) * scale};
}

}