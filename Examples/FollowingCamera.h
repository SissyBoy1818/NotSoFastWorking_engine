#pragma once

#include "Camera.h"
#include "Component.h"

#include "raylib.h"
#include <print>

using namespace nsfw;

class TransformComponent : public ecs::Component {
public:
    inline TransformComponent(const utils::Rectangle &rect)
        : m_rect(rect) {
        std::printf("TransformComponent successfully created\n");
    }

    inline void FrameUpdate(float dt) override {}

    inline void TickUpdate(float dt) override {}

    utils::Rectangle m_rect;
};

class Mouse : public ecs::GameObject {
public:
    inline Mouse() {
        utils::Rectangle r {x,y, 5,5};
        addComponent<TransformComponent>(r);
    }

    float x = 0;
    float y = 0;

    inline void FrameUpdate(float dt) override {
        auto [x, y] = GetMousePosition();
        auto t = std::dynamic_pointer_cast<TransformComponent>(m_components[0]);
        t->m_rect.position.x = x;
        t->m_rect.position.y = y;
    }
};

class FollowingCamera : public ecs::Component {
public:
    explicit FollowingCamera(std::shared_ptr<ecs::GameObject>&& owner, std::shared_ptr<ecs::GameObject>&& hunted);

    void FrameUpdate(float dt) override;

    void TickUpdate(float dt) override;

private:
    std::shared_ptr<ecs::GameObject> m_toFollow;
    std::shared_ptr<ecs::GameObject> m_owner;
};

inline FollowingCamera::FollowingCamera(std::shared_ptr<ecs::GameObject>&& owner, std::shared_ptr<ecs::GameObject>&& hunted)
    : m_toFollow(hunted)
    , m_owner(owner) {
    std::printf("FollowingCamera successfully created\n");
}

inline void FollowingCamera::FrameUpdate(float dt) {
    auto transform = m_owner->getComponent<TransformComponent>();
    auto targetPos = m_toFollow->getComponent<TransformComponent>();

    transform->m_rect.position = targetPos->m_rect.position;
}

inline void FollowingCamera::TickUpdate(float dt) {
}
