#pragma once

#include <unordered_map>
#include <typeindex>
#include "System.h"

namespace nsfw::ecs {

class SystemManager {
public:
    SystemManager() = default;

    template <std::derived_from<System> SYSTEM_TYPE, typename... Args>
    void registerSystem(Args&&... args);

    template <std::derived_from<System> SYSTEM_TYPE>
    void removeSystem();

    auto & getSystems();

private:
    std::unordered_map<std::type_index, std::shared_ptr<System>> m_systems;
};

// Реализация

template<std::derived_from<System> SYSTEM_TYPE, typename ... Args>
void SystemManager::registerSystem(Args &&...args) {
    m_systems[typeid(SYSTEM_TYPE)] = std::make_shared<System>(std::forward<Args>(args)...);
}

template<std::derived_from<System> SYSTEM_TYPE>
void SystemManager::removeSystem() {
    m_systems[typeid(SYSTEM_TYPE)].reset();
}

inline auto & SystemManager::getSystems() {
    return m_systems;
}

}
