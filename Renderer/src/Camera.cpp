#include "Camera.h"

#include "TransformComponent.h"

namespace nsfw::render {

Camera::Camera(const utils::Rectangle &rect) {
    addComponent<ecs::TransformComponent>(rect);
}

Camera::Camera(const utils::Vector2f position, const utils::Vector2f area) {
    utils::Rectangle rect{position, area};
    addComponent<ecs::TransformComponent>(rect);
}

utils::Vector2f Camera::CameraToWorldPosition(const utils::Vector2i point) const {
    const auto position = getComponent<ecs::TransformComponent>()->position();

    return {static_cast<float>(point.x) + position.x,
            static_cast<float>(point.y) + position.y};
}

utils::Vector2i Camera::WorldToCameraPosition(const utils::Vector2f point) const {
    const auto position = getComponent<ecs::TransformComponent>()->position();

    return {static_cast<int>(point.x) - static_cast<int>(position.x),
            static_cast<int>(point.y) - static_cast<int>(position.y)};
}

void Camera::zoom(const float factor) {
    auto transform = getComponent<ecs::TransformComponent>();
    auto size = transform->size();

    auto diff = size * (1 - factor);
    transform->move(diff/2.0f);
    size = size * factor;
}

Camera::operator Camera2D() const {
    const auto rect = getComponent<ecs::TransformComponent>()->rect();

    return Camera2D{rect.position.x, rect.position.y,
                    rect.size.x/2 + rect.position.x, rect.size.y/2 + rect.position.y,
                    0, 1.0f};
}

}
