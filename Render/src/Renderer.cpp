#include "Renderer.h"

#include <algorithm>

#include "raylib.h"

namespace nsfw::render {

Renderer::Renderer() = default;

Renderer::~Renderer() = default;

void Renderer::addTask(const utils::Vector2f origSize, const ecs::Transform &transform, const ecs::Drawable &drawable) {
    RenderTask task;
    task.originalSize = origSize;
    task.position = transform.rectangle.position;
    task.size = transform.rectangle.size;
    task.rotation = transform.rotation;
    task.scale = transform.scale;
    task.textureID = drawable.texture;

    m_renderQueue.push_back(task);
}

void Renderer::renderAll() {
    if (WindowShouldClose()) return;

    std::ranges::sort(m_renderQueue, [](const RenderTask &lhs, const RenderTask &rhs) -> bool
                      { return lhs.position.y < rhs.position.y; });

    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (const auto &[originalSize, position, size, rotation, scale, textureID] : m_renderQueue) {
        DrawTexturePro(*m_textureManager.getTexture(textureID),
                        {0,0, originalSize.x, originalSize.y},
                        {position.x+size.x/2, position.y+size.y/2, size.x, size.y},
                        {size.x/2, size.y/2},
                        rotation,
                        {255,255,255,255});
        // debug borders
        DrawRectangleLines(position.x, position.y, size.x, size.y, BLACK);
    }

    DrawText(std::to_string(GetFPS()).c_str(), 10, 10, 15, DARKGRAY);

    EndDrawing();

    const size_t oldSize = m_renderQueue.size();
    m_renderQueue.clear();
    m_renderQueue.reserve(oldSize);
}

TextureManager & Renderer::getTextureManager() {
    return m_textureManager;
}

}
