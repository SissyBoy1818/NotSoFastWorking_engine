#include "Level.h"

#include <ranges>

namespace nsfw::core {

void Level::update(float dt) {
    for (auto &layer : m_layerStack) {
        layer->onUpdate(dt);
    }

    for (auto &system: m_systemManager.getSystems() | std::views::values) {
        system->FrameUpdate(m_componentManager, dt);
    }
}

ecs::Entity Level::createEntity() {
    return m_entityManager.create();
}

void Level::destroyEntity(ecs::Entity entity) {
    m_entityManager.destroy(entity);
}

bool Level::isEntityValid(ecs::Entity entity) const {
    return m_entityManager.isAlive(entity);
}

void Level::onEvent(Event &event) {
    for (auto &layer : m_layerStack)
        layer->onEvent(event);

    for (auto &system : m_systemManager.getSystems() | std::views::values)
        system->OnEvent(m_componentManager, event);
}

}
