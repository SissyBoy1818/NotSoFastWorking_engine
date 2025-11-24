#pragma once

#include <memory>
#include <expected>
#include <iterator>
#include <stdexcept>
#include <typeindex>
#include <algorithm>
#include <unordered_map>
#include "ComponentArray.h"

namespace nsfw::ecs {

using Entity = uint32_t;

enum class ComponentLookupError {
    ComponentTypeNotRegistered,
    ComponentTypeWrongCast
};

class ComponentManager {
public:
    template <typename COMPONENT_TYPE>
    void addComponent(Entity entity, const COMPONENT_TYPE &component);

    template <typename... COMPONENT_TYPES>
    std::vector<Entity> getEntitiesWith();

    template <typename COMPONENT_TYPE>
    std::expected<COMPONENT_TYPE *, ComponentLookupError> getComponent(Entity entity);

private:
    std::unordered_map<std::type_index, std::shared_ptr<BaseComponentArray>> m_componentArrays;
};

// Реализация

template <typename COMPONENT_TYPE>
void ComponentManager::addComponent(const Entity entity, const COMPONENT_TYPE &component) {
    auto it = m_componentArrays.find(typeid(COMPONENT_TYPE));

    if (it == m_componentArrays.cend())
        it = m_componentArrays.emplace(typeid(COMPONENT_TYPE), std::make_shared<ComponentArray<COMPONENT_TYPE>>()).first;

    auto array = std::static_pointer_cast<ComponentArray<COMPONENT_TYPE>>(it->second);

    array->entities().push_back(entity);
    array->components().emplace_back(component);
}

template<typename... COMPONENT_TYPES>
std::vector<Entity> ComponentManager::getEntitiesWith() {
    if constexpr (sizeof...(COMPONENT_TYPES) == 0)
        return std::vector<Entity>{};

    std::vector<Entity> result;
    bool first = true;

    auto processComponent = [&]<typename T>() {
        const auto it = m_componentArrays.find(typeid(T));
        if (it == m_componentArrays.end()) {
            result.clear();
            return;
        }

        auto components = std::dynamic_pointer_cast<ComponentArray<T>>(it->second);
        if (!components)
            throw std::runtime_error("Failed to cast component array");

        auto& entities = components->entities();

        if (first) {
            result.insert(result.end(), entities.begin(), entities.end());
            first = false;
        } else {
            std::vector<Entity> intersection;
            std::set_intersection(
                result.begin(), result.end(),
                entities.begin(), entities.end(),
                std::inserter(intersection, intersection.begin())
            );
            result = std::move(intersection);
        }
    };

    (processComponent.template operator()<COMPONENT_TYPES>(), ...);

    return result;
}

template<typename COMPONENT_TYPE>
std::expected<COMPONENT_TYPE *, ComponentLookupError> ComponentManager::getComponent(const Entity entity) {
    auto it = m_componentArrays.find(typeid(COMPONENT_TYPE));

    if (it == m_componentArrays.cend())
        return std::unexpected{ComponentLookupError::ComponentTypeNotRegistered};

    auto array = std::dynamic_pointer_cast<ComponentArray<COMPONENT_TYPE>>(it->second);
    if (!array)
        return std::unexpected{ComponentLookupError::ComponentTypeWrongCast};

    auto& entities = array->entities();
    auto entityIt = std::find(entities.begin(), entities.end(), entity);

    if (entityIt == entities.end())
        return std::unexpected{ComponentLookupError::ComponentTypeNotRegistered};
    
    size_t index = std::distance(entities.begin(), entityIt);
    return &array->components()[index];
}

}
