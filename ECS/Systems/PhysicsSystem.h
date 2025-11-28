#pragma once

#include "Vector.h"
#include "System.h"
#include "CoreComponents.h"

namespace nsfw::ecs {

enum class BodyType {
    Static, Dynamic, Kinematic
};

struct PhysicBody {
    BodyType type;
    utils::Vector2f force;
    utils::Vector2f velocity;
    float mass;
};

class PhysicsSystem final : public System {
public:
    PhysicsSystem();

    void TickUpdate(ComponentManager &cm, float dt) override;
};

inline void PhysicsSystem::TickUpdate(ComponentManager &cm, float dt) {
    for (auto entity : cm.getEntitiesWith<PhysicBody>()) {
        auto physic = cm.getComponent<PhysicBody>(entity);
        auto transform = cm.getComponent<Transform>(entity);

        if (!transform.has_value() || !physic.has_value())
            continue;

        physic.value()->velocity += physic.value()->force / physic.value()->mass;
        transform.value()->rectangle.position += physic.value()->velocity;
    }
}

}
