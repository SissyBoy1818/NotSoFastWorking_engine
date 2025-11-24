#pragma once

#include <print>

#include "Event.h"
#include "System.h"
#include "CoreComponents.h"
#include "ComponentManager.h"
#include "InputEvents.h"

namespace nsfw::ecs {

class PanSystem final : public System {
public:
    PanSystem() = default;
    ~PanSystem() override = default;

    void FrameUpdate(ComponentManager& cm, float dt) override;
    void TickUpdate(ComponentManager& cm, float dt) override;
    void OnEvent(ComponentManager &cm, core::Event &e) override;

private:
    static bool onLMBPressed(ComponentManager &cm, const core::MousePressedEvent &mouseEvent);
    static bool onLMBReleased(ComponentManager &cm, const core::MouseReleasedEvent &mouseEvent);
    static bool onMouseMoved(ComponentManager &cm, const core::MouseMovedEvent &mouseEvent);

    static void ProcessPanning(PanningCamera &camera, Transform &transform, utils::Vector2f offset);
};

inline void PanSystem::FrameUpdate(ComponentManager &cm, float dt) {
}

inline void PanSystem::TickUpdate(ComponentManager &cm, float dt) {

}

inline void PanSystem::OnEvent(ComponentManager &cm, core::Event &e) {
    core::EventDispatcher dispatcher(e);

    dispatcher.dispatch<core::MouseReleasedEvent>([&](const core::MouseReleasedEvent &mouseEvent)
        { return onLMBReleased(cm, mouseEvent); });
    dispatcher.dispatch<core::MousePressedEvent>([&](const core::MousePressedEvent &mouseEvent)
        { return onLMBPressed(cm, mouseEvent); });
    dispatcher.dispatch<core::MouseMovedEvent>([&](const core::MouseMovedEvent &mouseEvent)
        { return onMouseMoved(cm, mouseEvent); });
}

inline bool PanSystem::onLMBPressed(ComponentManager &cm, const core::MousePressedEvent &mouseEvent) {
    if (mouseEvent.getMouseButton() != MOUSE_BUTTON_LEFT)
        return false;

    for (const Entity entity: cm.getEntitiesWith<PanningCamera>()) {
        auto camera = cm.getComponent<PanningCamera>(entity);
        if (!camera.has_value())
            continue;

        camera.value()->pannedPosition = mouseEvent.getPosition();
        camera.value()->isPanned = true;

        return true;
    }

    return false;
}

inline bool PanSystem::onLMBReleased(ComponentManager &cm, const core::MouseReleasedEvent &mouseEvent) {
    if (mouseEvent.getMouseButton() != MOUSE_BUTTON_LEFT)
        return false;

    for (const Entity entity: cm.getEntitiesWith<PanningCamera>()) {
        auto camera = cm.getComponent<PanningCamera>(entity);
        if (!camera.has_value())
            continue;

        camera.value()->isPanned = false;
        return true;
    }

    return false;
}

inline bool PanSystem::onMouseMoved(ComponentManager &cm, const core::MouseMovedEvent &mouseEvent) {
    for (const Entity entity: cm.getEntitiesWith<PanningCamera, Transform>()) {
        auto camera = cm.getComponent<PanningCamera>(entity);
        auto transform = cm.getComponent<Transform>(entity);
        if (!camera.has_value() || !transform.has_value())
            continue;
        if (!camera.value()->isPanned)
            continue;

        ProcessPanning(*camera.value(), *transform.value(), camera.value()->pannedPosition - mouseEvent.getMousePosition());
        return true;
    }
    return false;
}

inline void PanSystem::ProcessPanning(PanningCamera &camera, Transform &transform, utils::Vector2f offset) {
    const utils::Vector2f mousePos(GetMousePosition());
    offset.x /= transform.scale;
    offset.y /= transform.scale;
    transform.rectangle.position += offset;

    camera.pannedPosition = mousePos;
}

}
