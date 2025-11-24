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

ecs::EntityManager & Level::getEntityManager() {
    return m_entityManager;
}

void Level::onEvent(Event &event) {
    for (auto &layer : m_layerStack)
        layer->onEvent(event);

    for (auto &system : m_systemManager.getSystems() | std::views::values)
        system->OnEvent(m_componentManager, event);
}

}
