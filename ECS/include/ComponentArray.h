#pragma once

#include <vector>

namespace nsfw::ecs {

using Entity = uint32_t;

class BaseComponentArray {
public:
    virtual ~BaseComponentArray() = default;
};


template <typename COMPONENT_TYPE>
class ComponentArray final : public BaseComponentArray {
public:
    ComponentArray() = default;
    ~ComponentArray() override {};

    void addEntity(const Entity entity, const COMPONENT_TYPE &component) {
        m_components.push_back(component);
        m_entities.push_back(entity);
        // maybe sort
    }

    std::vector<COMPONENT_TYPE> & components() {
        return m_components;
    }

    std::vector<Entity> & entities() {
        return m_entities;
    }

private:
    std::vector<COMPONENT_TYPE> m_components;
    std::vector<Entity> m_entities;
};

}
