#include "Engine.h"

#include "raylib.h"

namespace nsfw::engine {

Engine::Engine(const int width, const int height, const std::string &title)
    : m_gameObjects()
    , m_camera(std::make_shared<render::Camera>(utils::Rectangle{0, 0, static_cast<float>(width),  static_cast<float>(height)})) {
    InitWindow(width, height, title.c_str());
    SetWindowState(FLAG_WINDOW_RESIZABLE);
}

Engine::~Engine() {
    CloseWindow();
}

void Engine::run() const {
    while (!WindowShouldClose()) {
        updateObjects();
        processPhysics();

        render();
    }
}

void Engine::updateObjects() const {
}

void Engine::processPhysics() const {
}

void Engine::render() const {

}

void Engine::addGameObject(const ecs::GameObject &object) {
    m_gameObjects.push_back(object);
}

}
