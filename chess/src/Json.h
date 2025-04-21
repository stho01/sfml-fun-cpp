//
// Created by stenm on 21.04.2025.
//

#pragma once

#include <nlohmann/json.hpp>
#include "SpriteAtlas.h"

void from_json(const nlohmann::json& j, SpriteAtlasRect& rect);
void from_json(const nlohmann::json& j, SpriteSheetDefinition& def);

