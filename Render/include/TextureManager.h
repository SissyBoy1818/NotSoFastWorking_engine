#pragma once

#include <string>
#include <expected>
#include <unordered_map>
#include "Entity.h"
#include "raylib.h"
#include "Vector.h"

namespace nsfw::render {

enum class TextureError {
    CannotFindFile,
    NoSuchID
};

class TextureManager {
public:
    TextureManager();
    ~TextureManager();

    TextureID loadTexture(const std::string &filePath, utils::Vector2f size);
    void unloadTexture(TextureID id);
    std::expected<Texture2D, TextureError> getTexture(TextureID id);

private:
    std::unordered_map<TextureID, Texture2D> m_textures;
};

}
