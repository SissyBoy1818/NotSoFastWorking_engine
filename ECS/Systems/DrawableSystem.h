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
    std::expected<Transform *, ComponentLookupError> cameraExp;
    for (const auto entity : cm.getEntitiesWith<CameraComponent>()) {
       cameraExp = cm.getComponent<Transform>(entity);
        if (cameraExp.has_value())
            break;
    }

    if (!cameraExp.has_value())
        return;
    const auto cameraTransform = *cameraExp.value();

    // Вычисляем видимую область камеры в мировых координатах с учетом масштаба
    utils::Rectangle cameraViewRect;
    cameraViewRect.position = cameraTransform.rectangle.position;
    cameraViewRect.size = cameraTransform.rectangle.size / cameraTransform.scale;

    for (const auto entity : cm.getEntitiesWith<Drawable, Transform>()) {
        auto drawable = cm.getComponent<Drawable>(entity);
        auto transform = cm.getComponent<Transform>(entity);
        if (!drawable.has_value() || !transform.has_value())
            continue;

        if (cameraViewRect.overlaps(transform.value()->rectangle)) {
            Transform tr;
            tr.rectangle = transform.value()->rectangle;
            tr.rectangle.position = render::WorldToCameraPosition(cameraTransform, tr.rectangle.position);
            tr.rectangle.size = tr.rectangle.size * cameraTransform.scale;
            m_renderer.addTask(transform.value()->rectangle.size, tr, *drawable.value());
        }
    }
}

inline void DrawableSystem::TickUpdate(ComponentManager &cm, float dt) {

}

}
