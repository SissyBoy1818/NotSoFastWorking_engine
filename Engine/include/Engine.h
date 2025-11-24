#pragma once

#include <string>
#include <chrono>
#include <utility>
#include "Level.h"
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

    void addLevel(std::shared_ptr<Level> &level);

    render::Renderer & getRenderer();

private:
    std::vector<std::shared_ptr<Level>> m_levels;
    render::Renderer m_renderer;

    bool m_isRunning = true;

    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
    TimePoint m_lastTime = std::chrono::steady_clock::now();
    float m_deltaTime = 0;

private:
    void updateTimers();
    bool handleEvent(Event &e);
};

}
