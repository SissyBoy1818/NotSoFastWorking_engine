#include "Renderer.h"

#include "raylib.h"

namespace nsfw::render {

Renderer::Renderer() = default;

Renderer::~Renderer() = default;

void Renderer::addTask(const ecs::Transform &transform, const ecs::Drawable &drawable) {
    RenderTask task;
    task.position = transform.rectangle.position;
    task.rotation = transform.rotation;
    task.scale = transform.scale;
    task.texture_id = drawable.texture;

    m_renderQueue.push_back(task);
}

void Renderer::renderAll() {
    BeginDrawing();

    for (const auto &[position, rotation, scale, texture_id]: m_renderQueue)
        DrawTextureEx(*m_textureManager.getTexture(texture_id), position, rotation, scale, {0,0,0,0});

    EndDrawing();

    const size_t oldSize = m_renderQueue.size();
    m_renderQueue.clear();
    m_renderQueue.reserve(oldSize);
}

}
