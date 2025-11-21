#pragma  once

#include "ComponentManager.h"

namespace nsfw::ecs {

/**
 * \brief Базовый класс для описания систем
 */
class System {
public:
    virtual ~System() = default;

    System() = default;

    virtual void FrameUpdate(ComponentManager& cm, float dt) = 0;
    virtual void TickUpdate(ComponentManager& cm, float dt) = 0;

};

}