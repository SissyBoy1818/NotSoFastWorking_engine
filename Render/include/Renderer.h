#pragma once

#include <vector>
#include "CoreComponents.h"

namespace nsfw::render {

struct RenderTask {
    utils::Vector2f position;
    float scale;
    ecs::TextureID texture_id;
};

class Renderer {
public:
    Renderer();
    ~Renderer();

    void addTask(const ecs::Transform &, const ecs::Drawable &);
    void renderAll();

private:
    TextureManager m_textureManager;

    std::vector<RenderTask> m_renderQueue;
};

}