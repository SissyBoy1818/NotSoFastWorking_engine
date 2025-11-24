#include "TextureManager.h"

namespace nsfw::render {

TextureManager::TextureManager() = default;

TextureManager::~TextureManager() = default;

TextureID TextureManager::loadTexture(const std::string &filePath, utils::Vector2f size) {
    auto image = LoadImage(filePath.c_str());
    ImageResize(&image, size.x, size.y);

    const auto texture = LoadTextureFromImage(image);
    UnloadImage(image);
    m_textures[texture.id] = texture;
    return texture.id;
}

void TextureManager::unloadTexture(const TextureID id) {
    if (m_textures.contains(id))
        UnloadTexture(m_textures[id]);
}

std::expected<Texture2D, TextureError> TextureManager::getTexture(const TextureID id) {
    if (m_textures.contains(id))
        return m_textures[id];

    return std::unexpected(TextureError::NoSuchID);
}

}
