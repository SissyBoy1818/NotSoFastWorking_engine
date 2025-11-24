#pragma once

#include "Event.h"
#include "System.h"
#include "InputEvents.h"
#include "CoreComponents.h"

namespace nsfw::ecs {

class ZoomingSystem final : public System {
public:
    ZoomingSystem() = default;
    ~ZoomingSystem() override = default;

    void OnEvent(ComponentManager &cm, core::Event &e) override;

private:
    bool onMouseScroll(ComponentManager &cm, core::MouseScrolledEvent &e);
    void ProcessZoom(Transform &transform, ZoomableCamera &zoom,  float wheelMove);
};

inline void ZoomingSystem::OnEvent(ComponentManager &cm, core::Event &e) {
    core::EventDispatcher dispatcher(e);

    dispatcher.dispatch<core::MouseScrolledEvent>([&](core::MouseScrolledEvent &mouseEvent)
        { return onMouseScroll(cm, mouseEvent); });
}

inline bool ZoomingSystem::onMouseScroll(ComponentManager &cm, core::MouseScrolledEvent &e) {
    for (auto entity : cm.getEntitiesWith<ZoomableCamera, Transform>()) {
        auto transform = cm.getComponent<Transform>(entity);
        auto zoom = cm.getComponent<ZoomableCamera>(entity);

        if (!zoom.has_value() || !transform.has_value())
            continue;

        ProcessZoom(*transform.value(), *zoom.value(), e.getScroll());
        return true;
    }
    return false;
}

inline void ZoomingSystem::ProcessZoom(Transform &transform, ZoomableCamera &zoom, const float wheelMove) {
    const utils::Vector2f mousePosition{GetMousePosition()};
    const auto oldWorldMousePosition = render::CameraToWorldPosition(transform, mousePosition);
    const auto oldPosition = transform.rectangle.position;
    const auto oldScale = transform.scale;

    if (wheelMove > 0)
        transform.scale = std::min(oldScale + zoom.delta, zoom.maxZoom);
    else
        transform.scale = std::max(oldScale - zoom.delta, zoom.minZoom);

    const auto newWorldMousePosition = render::CameraToWorldPosition(transform, mousePosition);
    auto offset = oldWorldMousePosition - newWorldMousePosition;
    transform.rectangle.position = oldPosition + offset;
}

}
