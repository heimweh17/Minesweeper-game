#include <unordered_map>
#include "TextureManager.h"

std::unordered_map<std::string, sf::Texture> TextureManager::textures;

sf::Texture& TextureManager::GetTexture(const std::string& filename) {
    if (textures.find(filename) == textures.end()) {
        sf::Texture texture;
        if (!texture.loadFromFile("files/images/" + filename)) {
            throw std::runtime_error("Failed to load texture: " + filename);
        }
        textures[filename] = texture;
    }
    return textures[filename];
}

void TextureManager::Clear() {
    textures.clear();
}