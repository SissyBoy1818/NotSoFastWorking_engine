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
    const auto &transform = getComponent<ecs::TransformComponent>();
    const auto position = transform->position();
    const auto scale = transform->scale();

    return {static_cast<float>(point.x) / scale.x + position.x,
            static_cast<float>(point.y) / scale.y + position.y};
}

utils::Vector2i Camera::WorldToCameraPosition(const utils::Vector2f point) const {
    const auto &transform = getComponent<ecs::TransformComponent>();
    const auto position = transform->position();
    const auto scale = transform->scale();

    return {static_cast<int>((point.x - position.x) * scale.x),
            static_cast<int>((point.y - position.y) * scale.y)};
}

Camera::operator Camera2D() const {
    const auto rect = getComponent<ecs::TransformComponent>()->rect();

    return Camera2D{rect.position.x, rect.position.y,
                    rect.size.x/2 + rect.position.x, rect.size.y/2 + rect.position.y,
                    0, 1.0f};
}

}
