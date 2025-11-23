#pragma once

#include <vector>
#include <queue>
#include "Entity.h"

namespace nsfw::ecs {

class EntityManager {
public:
    EntityManager(uint32_t reserved = 0);

    [[nodiscard]] Entity create();

    void destroy(Entity entity);

    [[nodiscard]] bool isAlive(Entity) const;

private:
    static constexpr uint32_t INDEX_BITS = 22;
    static constexpr uint32_t GENERATION_BITS = 10;

    static constexpr uint32_t INDEX_MASK = (1u << INDEX_BITS) - 1u;
    static constexpr uint32_t GENERATION_MASK   = (1u << GENERATION_BITS) - 1u;

    std::queue<uint32_t> m_freeIndex;
    std::vector<uint32_t> m_generations;

private:
    static uint32_t getIndex(Entity entity) ;

    static uint32_t getGeneration(Entity entity) ;

    static Entity makeId(uint32_t generation, uint32_t index) ;

};

}
