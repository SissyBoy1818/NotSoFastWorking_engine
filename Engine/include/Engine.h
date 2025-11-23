#pragma once

#include <string>
#include <utility>
#include "System.h"
#include "SystemManager.h"
#include "EntityManager.h"

namespace nsfw::engine {

struct EngineConfig {
    int width, height;
    std::string title;

    EngineConfig(int w, int h, std::string t) : width(w), height(h), title(std::move(t)) {};
};

class Engine {
public:
    explicit Engine(const EngineConfig &config);
    ~Engine();

    void run();
    void pause();

    void gameLoop();

    template <std::derived_from<ecs::System> SYSTEM_TYPE, typename... Args>
    void registerSystem(Args&&... args);

    ecs::Entity createEntity();

    template<typename COMPONENT_TYPE>
    void addComponent(ecs::Entity entity, COMPONENT_TYPE component);

private:
    ecs::SystemManager m_systemManager;
    ecs::EntityManager m_entityManager;
    ecs::ComponentManager m_componentManager;
    bool m_isRunning = true;

private:
    void updateObjects(float dt);
};

// Реализация

template<std::derived_from<ecs::System> SYSTEM_TYPE, typename ... Args>
void Engine::registerSystem(Args &&...args) {
    m_systemManager.registerSystem<SYSTEM_TYPE>(std::make_shared<SYSTEM_TYPE>(args)...);
}

template<typename COMPONENT_TYPE>
void Engine::addComponent(ecs::Entity entity, COMPONENT_TYPE component) {
    m_componentManager.addComponent(entity, component);
}

}
