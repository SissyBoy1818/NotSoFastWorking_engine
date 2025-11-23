#pragma once

#include <string>
#include <chrono>
#include <utility>
#include "System.h"
#include "SystemManager.h"
#include "EntityManager.h"
#include "Layer.h"
#include "Renderer.h"

namespace nsfw::core {

struct EngineConfig {
    int width, height;
    std::string title;

    EngineConfig(int w, int h, std::string t) : width(w), height(h), title(std::move(t)) {};
};

class Engine {
public:
    explicit Engine(const EngineConfig &config);
    ~Engine();

    void run();
    void pause();

    void gameLoop();

private:
    std::vector<Level> m_levels;
    render::Renderer m_renderer;

    bool m_isRunning = true;

    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
    TimePoint m_lastTime = std::chrono::steady_clock::now();
    float m_deltaTime = 0;

private:
    void updateTimers();
};

}
