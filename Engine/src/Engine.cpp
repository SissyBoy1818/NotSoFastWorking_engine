#include "Engine.h"

#include "EventTranslator.h"
#include "raylib.h"

namespace nsfw::core {

Engine::Engine(const EngineConfig &config) {
    InitWindow(config.width, config.height, config.title.c_str());
}

Engine::~Engine() = default;

void Engine::run() {
    m_isRunning = true;

    gameLoop();
}

void Engine::pause() {
    m_isRunning = false;
}

void Engine::gameLoop() {
    while (m_isRunning) {

        // Handle input
        EventTranslator::checkEvents([this](Event& e) -> bool {
                                         return this->handleEvent(e);
                                     });

        updateTimers();

        for (auto &level : m_levels)
            level.update(m_deltaTime);

        m_renderer.renderAll();
    }
}

void Engine::updateTimers() {
    const TimePoint time = std::chrono::steady_clock::now();
    m_deltaTime = std::chrono::duration<float>(time - m_lastTime).count();
    m_lastTime = time;
}

bool Engine::handleEvent(Event &e) {
    EventDispatcher  dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>([](WindowCloseEvent &) {
            CloseWindow();
            return true;
        });


    for (auto &level : m_levels)
        level.onEvent(e);

    return false;
}

}
