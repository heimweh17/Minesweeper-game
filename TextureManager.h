#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager {
private:
    static std::unordered_map<std::string, sf::Texture> textures;

public:
    static sf::Texture& GetTexture(const std::string& filename);
    static void Clear();  // optional, to free memory manually
};