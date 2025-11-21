#pragma once

#include "System.h"
#include "CoreComponents.h"
#include "ZoomingCamera.h"

namespace nsfw::ecs {

class ZoomingSystem final : public System {
public:
    ZoomingSystem() = default;
    ~ZoomingSystem() override = default;

    void FrameUpdate(ComponentManager &cm, float dt) override;
    void TickUpdate(ComponentManager &cm, float dt) override;

private:
    void ProcessZoom(Transform &transform, ZoomableCamera &zoom);
};


inline void ZoomingSystem::FrameUpdate(ComponentManager &cm, float dt) {
    for (auto entity : cm.getEntitiesWith<ZoomableCamera, Transform>()) {
        auto transform = cm.getComponent<Transform>(entity);
        auto zoom = cm.getComponent<ZoomableCamera>(entity);

        if (!zoom.has_value() || !transform.has_value())
            continue;

        ProcessZoom(*transform, *zoom);
    }
}

inline void ZoomingSystem::TickUpdate(ComponentManager &cm, float dt) {

}

inline void ZoomingSystem::ProcessZoom(Transform &transform, ZoomableCamera &zoom) {
    const auto wheelMove = GetMouseWheelMove();
    if (wheelMove == 0)
        return;

    const utils::Vector2f mousePosition{GetMousePosition()};
    const auto oldWorldMousePosition = render::CameraToWorldPosition(transform, mousePosition);
    const auto oldPosition = transform.rectangle.position;
    const auto oldScale = transform.scale;

    if (wheelMove > 0)
        transform.scale = oldScale + zoom.delta;
    else
        transform.scale = oldScale - zoom.delta;

    const auto newWorldMousePosition = render::CameraToWorldPosition(transform, mousePosition);
    auto offset = oldWorldMousePosition - newWorldMousePosition;
    transform.rectangle.position = oldPosition + offset;
}

}
