#pragma once

#include <string>
#include "GameObject.h"
#include "Camera.h"

namespace nsfw::engine {

class Engine {
public:
    Engine(int width, int height, const std::string &title);
    ~Engine();

    void run() const;

    void updateObjects() const;

    void processPhysics() const;

    void render() const;

    void addGameObject(const ecs::GameObject &object);

private:
    std::vector<ecs::GameObject> m_gameObjects;
    std::shared_ptr<render::Camera> m_camera;

};

}