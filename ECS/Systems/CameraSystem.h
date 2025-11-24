#pragma once

#include "Event.h"
#include "System.h"
#include "WindowEvents.h"
#include "CoreComponents.h"

namespace nsfw::ecs {

class CameraSystem final : public System {
public:
    ~CameraSystem() override = default;

    void OnEvent(ComponentManager &cm, core::Event &e) override;

private:
    static bool onWindowResized(ComponentManager &cm, core::WindowResizedEvent &windowEvent);
};

inline void CameraSystem::OnEvent(ComponentManager &cm, core::Event &e) {
    core::EventDispatcher dispatcher(e);

    dispatcher.dispatch<core::WindowResizedEvent>([&](core::WindowResizedEvent &windowEvent)
        { return onWindowResized(cm, windowEvent); });
}

inline bool CameraSystem::onWindowResized(ComponentManager &cm, core::WindowResizedEvent &windowEvent) {
    for (const auto entity : cm.getEntitiesWith<CameraComponent>()) {
        auto transform = cm.getComponent<Transform>(entity);
        if (!transform.has_value())
            continue;

        transform.value()->rectangle.size = windowEvent.getSize();
        return true;
    }
    return false;
}

}
