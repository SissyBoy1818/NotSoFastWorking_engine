#pragma once

#include "System.h"
#include "Renderer.h"
#include "CoreComponents.h"

namespace nsfw::ecs {

class DrawableSystem final : public System {
public:
    DrawableSystem(render::Renderer &renderer) : m_renderer(renderer) {};
    ~DrawableSystem() override = default;

    void FrameUpdate(ComponentManager& cm, float dt) override;
    void TickUpdate(ComponentManager& cm, float dt) override;

private:
    render::Renderer &m_renderer;
};


inline void DrawableSystem::FrameUpdate(ComponentManager &cm, float dt) {
    for (auto entity : cm.getEntitiesWith<Drawable, Transform>()) {
        auto drawable = cm.getComponent<Drawable>(entity);
        auto transform = cm.getComponent<Transform>(entity);
        if (!drawable.has_value() || !transform.has_value())
            continue;

        m_renderer.addTask(*transform, *drawable);
    }
}

inline void DrawableSystem::TickUpdate(ComponentManager &cm, float dt) {

}

}
