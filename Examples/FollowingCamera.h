#pragma once

#include "Camera.h"
#include "Component.h"
#include "TransformComponent.h"
#include "raylib.h"
#include <print>

using namespace nsfw;

class Mouse : public ecs::GameObject {
public:
    inline Mouse() {
        utils::Rectangle r {x,y, 5,5};
        addComponent<ecs::TransformComponent>(r);
    }

    float x = 0;
    float y = 0;

    inline void FrameUpdate(float dt) override {
        auto [x, y] = GetMousePosition();
        auto t = std::dynamic_pointer_cast<ecs::TransformComponent>(m_components[0]);
        t->setPosition({x, y});
    }
};

class FollowingCamera : public ecs::Component {
public:
    explicit FollowingCamera(std::shared_ptr<ecs::GameObject>&& camera, std::shared_ptr<ecs::GameObject>&& hunted);

    void FrameUpdate(float dt) override;

    void TickUpdate(float dt) override;

private:
    std::shared_ptr<ecs::GameObject> m_toFollow;
    std::shared_ptr<ecs::GameObject> m_camera;
};

inline FollowingCamera::FollowingCamera(std::shared_ptr<ecs::GameObject>&& camera, std::shared_ptr<ecs::GameObject>&& hunted)
    : m_toFollow(hunted)
    , m_camera(camera) {
    std::printf("FollowingCamera successfully created\n");
}

inline void FollowingCamera::FrameUpdate(float dt) {
    auto transform = m_camera->getComponent<ecs::TransformComponent>();
    auto targetPos = m_toFollow->getComponent<ecs::TransformComponent>();

    transform->setPosition(targetPos->position() - transform->size()/2);
}

inline void FollowingCamera::TickUpdate(float dt) {
}
