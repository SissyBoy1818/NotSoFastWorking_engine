#pragma once

#include "System.h"
#include "CoreComponents.h"
#include "ComponentManager.h"

namespace nsfw::ecs {

class PanSystem final : public System {
public:
    PanSystem() = default;
    ~PanSystem() override = default;

    void FrameUpdate(ComponentManager& cm, float dt) override;
    void TickUpdate(ComponentManager& cm, float dt) override;

private:
    void ProcessPanning(PanningCamera &camera, Transform &transform);
};

inline void PanSystem::FrameUpdate(ComponentManager &cm, float dt) {
    for (Entity entity: cm.getEntitiesWith<PanningCamera, Transform>()) {
        auto camera = cm.getComponent<PanningCamera>(entity);
        auto transform = cm.getComponent<Transform>(entity);
        if (!camera.has_value() || !transform.has_value())
            continue;

        if (!camera->isPanned && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            camera->pannedPosition = GetMousePosition();
            camera->isPanned = true;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            camera->isPanned = false;

        if (camera->isPanned) {
            ProcessPanning(*camera, *transform);
        }
    }
}

inline void PanSystem::TickUpdate(ComponentManager &cm, float dt) {

}

inline void PanSystem::ProcessPanning(PanningCamera &camera, Transform &transform) {
    const utils::Vector2f mousePos(GetMousePosition());
    auto offset = camera.pannedPosition - mousePos;
    offset.x /= transform.scale.x;
    offset.y /= transform.scale.y;
    transform.rectangle.position += offset;

    camera.pannedPosition = mousePos;
}

}
