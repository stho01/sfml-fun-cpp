//
// Created by stenm on 21.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

struct SpriteAtlasRect {
    int left;
    int top;
    int width;
    int height;

    sf::IntRect toIntRect() const {
        return sf::IntRect({left, top}, {width, height});
    }
};

struct SpriteSheetDefinition {
    std::string texture;
    std::unordered_map<std::string, SpriteAtlasRect> sprites;
};

class SpriteAtlas {
public:
    void load(const std::string& atlasDefinition);
    sf::Sprite* getSprite(const std::string& name);

private:
    std::unique_ptr<sf::Texture> _texture;
    std::unordered_map<std::string, std::unique_ptr<sf::Sprite>> _sprites;

    static std::string _normalizeName(const std::string& name);
};

