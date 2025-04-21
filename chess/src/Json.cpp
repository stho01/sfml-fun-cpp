//
// Created by stenm on 21.04.2025.
//

#include "Json.h"

void from_json(const nlohmann::json& j, SpriteAtlasRect& rect) {
    rect.left = j.at("left").get<int>();
    rect.top = j.at("top").get<int>();
    rect.width = j.at("width").get<int>();
    rect.height = j.at("height").get<int>();
}

// Fortell hvordan SpriteSheetDefinition skal leses
void from_json(const nlohmann::json& j, SpriteSheetDefinition& def) {
    def.texture = j.at("Texture").get<std::string>();
    def.sprites = j.at("Sprites").get<std::unordered_map<std::string, SpriteAtlasRect>>();
}