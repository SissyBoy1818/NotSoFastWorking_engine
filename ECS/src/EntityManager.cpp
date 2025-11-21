#include "EntityManager.h"

namespace nsfw::ecs {

EntityManager::EntityManager(const uint32_t reserved) {
    if (reserved == 0)
        return;

    m_generations.reserve(reserved);

    for (uint32_t i = 0; i < reserved; i++) {
        m_generations.push_back(0);
        m_freeIndex.push(i);
    }
}

Entity EntityManager::create() {
    uint32_t index;
    if (!m_freeIndex.empty()) {
        index = m_freeIndex.front();
        m_freeIndex.pop();
    } else {
        index = static_cast<uint32_t>(m_generations.size());
        m_generations.push_back(0);
    }

    return makeId(m_generations[index], index);
}

void EntityManager::destroy(const Entity entity) {
    const uint32_t index = getIndex(entity);
    if (index >= m_generations.size()) return;

    ++m_generations[index];

    m_freeIndex.push(index);
}

bool EntityManager::isAlive(const Entity entity) const {
    const uint32_t index = getIndex(entity);
    if (index >= m_generations.size()) return false;

    uint32_t generation = getGeneration(entity);
    return m_generations[index] == generation;
}

uint32_t EntityManager::getIndex(const Entity entity) {
    return entity & INDEX_MASK;
}

uint32_t EntityManager::getGeneration(const Entity entity) {
    return (entity >> INDEX_BITS) & GENERATION_MASK;
}

Entity EntityManager::makeId(const uint32_t generation, const uint32_t index) {
    return  (generation << INDEX_BITS) | index;
}

}
