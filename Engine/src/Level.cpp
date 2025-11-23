#include "Level.h"

namespace nsfw::core {

void Level::update(float dt) {
    for (auto &layer : m_layerStack) {
        layer->onUpdate(dt);
    }
}

ecs::EntityManager & Level::getEntityManager() {
    return m_entityManager;
}

void Level::onEvent(Event &event) {
    for (auto &layer : m_layerStack) {
        layer->onEvent(event);
    }
}

}
