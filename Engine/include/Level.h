#pragma once

#include "EntityManager.h"
#include "SystemManager.h"
#include "ComponentManager.h"

namespace nsfw::core {

class Level {
public:
    Level() = default;

    [[nodiscard]] Entity createEntity();

    template <std::derived_from<ecs::System> SYSTEM_TYPE, typename... Args>
    void registerSystem(Args&&... args);

    template<typename COMPONENT_TYPE>
    void addComponent(ecs::Entity entity, COMPONENT_TYPE component);

    template <std::derived_from<Layer> LAYER_TYPE>
    void pushLayer();

    template <std::derived_from<Layer> LAYER_TYPE>
    LAYER_TYPE * getLayer() const;

    void update(float dt);

private:
    ecs::SystemManager m_systemManager;
    ecs::EntityManager m_entityManager;
    ecs::ComponentManager m_componentManager;

    std::vector<std::unique_ptr<Layer>> m_layerStack;
};

// Реализация

template<std::derived_from<ecs::System> SYSTEM_TYPE, typename ... Args>
void Level::registerSystem(Args &&...args) {
    m_systemManager.registerSystem<SYSTEM_TYPE>(std::make_shared<SYSTEM_TYPE>(args)...);
}

template<typename COMPONENT_TYPE>
void Level::addComponent(ecs::Entity entity, COMPONENT_TYPE component) {
    m_componentManager.addComponent(entity, component);
}

template<std::derived_from<Layer> LAYER_TYPE>
void Engine::pushLayer() {
    m_layerStack.push_back(std::make_unique<LAYER_TYPE>());
}

template<std::derived_from<Layer> LAYER_TYPE>
LAYER_TYPE * Engine::getLayer() const {
    for (const auto &layer : m_layerStack) {
        if (auto casted = dynamic_cast<LAYER_TYPE*>(layer.get()))
            return casted;
    }
    return nullptr;
}

}