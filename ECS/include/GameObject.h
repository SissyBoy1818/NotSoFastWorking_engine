#pragma once

#include "Component.h"
#include <vector>
#include <memory>
#include <type_traits>

namespace nsfw::ecs {

class GameObject {
public:
    GameObject() = default;
    virtual ~GameObject() = default;

    /// Обновляет объект с фиксированным шагом времени
    virtual void TickUpdate(float dt);
    /// Обновляет объект каждый кадр
    virtual void FrameUpdate(float dt);

    /**
     * \brief Метод для добавления новой компоненты игрового объекта
     * \tparam T Класс компоненты
     * \tparam Args Типы аргументов конструктора компоненты
     * \param args Аргументы конструктора компоненты
     */
    template<typename T, typename... Args>
    void addComponent(Args&&... args);

    /**
     * \brief Метод для поиска компонента у объекта
     * \tparam T Тип компонента
     * \return Указатель на компонент
     */
    template<typename T>
    std::shared_ptr<T> getComponent() const;

protected:
    std::vector<std::shared_ptr<Component>> m_components;
};


// Реализация

inline void GameObject::TickUpdate(const float dt) {
    for (const auto &component : m_components)
        component->TickUpdate(dt);
}

inline void GameObject::FrameUpdate(const float dt) {
    for (const auto &component : m_components)
        component->FrameUpdate(dt);
}

template<typename T, typename... Args>
void GameObject::addComponent(Args&&... args) {
    m_components.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
}

template<typename T>
std::shared_ptr<T> GameObject::getComponent() const {
    for (const auto &component : m_components)
        if (auto casted = std::dynamic_pointer_cast<T>(component))
            return casted;

    return nullptr;
}

}