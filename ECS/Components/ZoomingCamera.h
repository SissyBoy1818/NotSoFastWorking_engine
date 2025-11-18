#pragma once

#include "Camera.h"

#include "Component.h"
#include "raylib.h"
#include "TransformComponent.h"

namespace nsfw::ecs {

class ZoomingCamera final : public Component {
public:
    explicit ZoomingCamera(const std::shared_ptr<render::Camera> &camera);

    void FrameUpdate(float dt) override;
    void TickUpdate(float dt) override;

private:
    void processZooming();

private:
    std::shared_ptr<render::Camera> m_camera;
};

// Реализация

inline ZoomingCamera::ZoomingCamera(const std::shared_ptr<render::Camera> &camera)
    : m_camera(camera) {}

inline void ZoomingCamera::FrameUpdate(float dt) {
    processZooming();
}

inline void ZoomingCamera::TickUpdate(float dt) {}

inline void ZoomingCamera::processZooming() {
    const auto wheelMove = GetMouseWheelMove();
    if (wheelMove == 0)
        return;

    const utils::Vector2i mousePosition{GetMousePosition()};
    const auto oldWorldMousePosition = m_camera->CameraToWorldPosition(mousePosition);
    auto transform = m_camera->getComponent<TransformComponent>();
    const auto oldPosition = transform->position();
    const auto oldScale = transform->scale();

    const utils::Vector2f delta{0.05f, 0.05f};
    if (wheelMove > 0)
        transform->setScale(oldScale+delta);
    else
        transform->setScale(oldScale-delta);

    const auto newWorldMousePosition = m_camera->CameraToWorldPosition(mousePosition);
    auto a = oldWorldMousePosition - newWorldMousePosition;
    transform->setPosition(oldPosition + a);
}

}
