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

    virtual void FrameUpdate(ComponentManager &cm, float dt) {};
    virtual void TickUpdate(ComponentManager &cm, float dt) {};
    virtual void OnEvent(ComponentManager &cm, core::Event &e) {};

protected:
    uint8_t tps = 20; ///< Ticks per second
};

}