#pragma once

#include "Component.h"
#include "Camera.h"
#include "Vector.h"
#include "raylib.h"
#include "TransformComponent.h"

namespace nsfw::ecs {

class PanningCamera final : public Component {
public:
    explicit PanningCamera(std::shared_ptr<render::Camera> &camera);

    /**
     * \brief Отслеживание пользовательского ввода
     * \param dt Не используется
     */
    void FrameUpdate(float dt) override;

    /// Не используется
    void TickUpdate(float dt) override;

private:
    /**
     * \brief Обновление позиции камеры, если зажата ЛКМ
     */
    void ProcessPanning();

private:
    std::shared_ptr<render::Camera> &m_camera; ///< Ссылка на камеру
    utils::Vector2f m_pannedPosition; ///< Позиция в координатах экрана
    bool m_isPanned = false; ///< Зажата ли ЛКМ
};

// Реализация

inline PanningCamera::PanningCamera(std::shared_ptr<render::Camera> &camera)
    : m_camera(camera) {}

inline void PanningCamera::FrameUpdate(float dt) {
    if (!m_isPanned && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        m_pannedPosition = GetMousePosition();
        m_isPanned = true;
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        m_isPanned = false;

    if (m_isPanned)
        ProcessPanning();
}

inline void PanningCamera::TickUpdate(float dt) {}

inline void PanningCamera::ProcessPanning() {
    auto transform = m_camera->getComponent<TransformComponent>();
    utils::Vector2f mousePos(GetMousePosition());
    auto newPos = m_pannedPosition - mousePos;
    newPos.x /= transform->scale().x;
    newPos.y /= transform->scale().y;
    transform->move(newPos);

    m_pannedPosition = mousePos;
}

}
