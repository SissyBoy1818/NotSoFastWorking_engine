#include "TextureManager.h"

namespace nsfw::render {

TextureManager::TextureManager() = default;

TextureManager::~TextureManager() = default;

TextureID TextureManager::loadTexture(const std::string &filePath) {
    const auto texture = LoadTexture(filePath.c_str());
    m_textures[texture.id] = texture;
    return texture.id;
}

void TextureManager::unloadTexture(TextureID id) {
    if (m_textures.contains(id))
        UnloadTexture(m_textures[id]);
}

std::expected<Texture2D, TextureError> TextureManager::getTexture(TextureID id) {
    if (m_textures.contains(id))
        return m_textures[id];

    return std::unexpected(TextureError::NoSuchID);
}

}
