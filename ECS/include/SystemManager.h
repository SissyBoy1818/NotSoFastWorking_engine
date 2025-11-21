#pragma once

#include <unordered_map>
#include <typeindex>
#include "System.h"

namespace nsfw::ecs {

class SystemManager {
public:
    SystemManager() = default;

    void registerSystem(std::shared_ptr<System> system);

    void runSystems();

private:
    std::unordered_map<std::type_index, std::shared_ptr<System>> m_systems;
};

}