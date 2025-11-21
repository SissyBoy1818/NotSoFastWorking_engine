#pragma once

#include <string>
#include "SystemManager.h"
#include "EntityManager.h"

namespace nsfw::engine {

struct EngineConfig {
    int width, height;
    std::string title;
};

class Engine {
public:
    explicit Engine(const EngineConfig &config);
    ~Engine();

    void run();
    void pause();
    void resume();

    void updateObjects(float dt);

    template <typename SYSTEM_TYPE, typename... Args>
    SYSTEM_TYPE* registerSystem(Args&&... args);

    void addGameObject(ecs::Entity entity);

    template<typename COMPONENT_TYPE>
    void addComponent(ecs::Entity entity, COMPONENT_TYPE component);

private:
    ecs::SystemManager m_systemManager;
    ecs::EntityManager m_entityManager;
    ecs::ComponentManager m_componentManager;
};

}
