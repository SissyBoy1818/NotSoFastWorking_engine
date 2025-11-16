#pragma once

namespace nsfw::ecs {

/**
 * \class Component
 * \brief Базовый класс для реализации компонентов объектов
 *
 * Класс для создания пользовательских компонент игровых объектов для управления их поведением
 */
class Component {
public:
    virtual ~Component() = default;

    /// Обновление компоненты каждый кадр
    virtual void FrameUpdate(float dt) = 0;
    /// Обновление компоненты каждый тик
    virtual void TickUpdate(float dt) = 0;
};

}