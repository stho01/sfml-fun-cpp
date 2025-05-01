//
// Created by stenm on 21.04.2025.
//

#include "SpriteAtlas.h"
#include <fstream>
#include <extensions/extensions.h>
#include <nlohmann/json.hpp>
#include "Json.h"

void SpriteAtlas::load(const std::string& atlasDefinition) {
    std::ifstream file(atlasDefinition);
    if (!file) {
        throw std::runtime_error("Failed to open atlas definition file: " + atlasDefinition);
    }

    nlohmann::json json;
    file >> json;
    auto [texture, sprites] = json.get<SpriteSheetDefinition>();

    const auto& texturePath = "assets/" + texture;
    Logger::Info("Loading sprite atlas: {}", texturePath);
    _texture = std::make_unique<sf::Texture>(texturePath);
    for (const auto& [name, rect] : sprites) {
        auto key = _normalizeName(name);
        sf::IntRect intRect = rect.toIntRect();
        _sprites[key] = std::make_unique<sf::Sprite>(*_texture, intRect);
    }
}

sf::Sprite* SpriteAtlas::getSprite(const std::string& name) {
    const auto key = _normalizeName(name);

    if (const auto search = _sprites.find(key); search != _sprites.end()) {
        return search->second.get();
    }

    return nullptr;
}


std::string SpriteAtlas::_normalizeName(const std::string& name) {
    std::string normalizedName = name;
    normalizedName = stho::String::trim(normalizedName);
    normalizedName = stho::String::toLower(normalizedName);
    return normalizedName;
}