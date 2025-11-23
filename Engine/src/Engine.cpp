#include "Engine.h"

#include <ranges>

#include "raylib.h"

// TODO

namespace nsfw::engine {

Engine::Engine(const EngineConfig &config) {
    InitWindow(config.width, config.height, config.title.c_str());
}

Engine::~Engine() = default;

void Engine::run() {
    m_isRunning = true;
}

void Engine::pause() {
    m_isRunning = false;
}

void Engine::gameLoop() {
    // Handle input
    // update Layers (updateObjects в Layers)
    // render
}

ecs::Entity Engine::createEntity() {
return m_entityManager.create();
}

void Engine::updateObjects(float dt) {
    for (auto &system: m_systemManager.getSystems() | std::views::values) {
        system->FrameUpdate(m_componentManager, dt);
        system->TickUpdate(m_componentManager, dt);
    }
}

}