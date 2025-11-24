#pragma once

#include <vector>
#include "CoreComponents.h"
#include "TextureManager.h"

namespace nsfw::render {

struct RenderTask {
    utils::Vector2f originalSize;
    utils::Vector2f position;
    utils::Vector2f size;
    float rotation;
    float scale;
    TextureID textureID;
};

class Renderer {
public:
    Renderer();
    ~Renderer();

    void addTask(const utils::Vector2f origSize, const ecs::Transform &transform, const ecs::Drawable &drawable);
    void renderAll();

    TextureManager & getTextureManager();

private:
    TextureManager m_textureManager;

    std::vector<RenderTask> m_renderQueue;
};

}