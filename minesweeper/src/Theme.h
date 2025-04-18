//
// Created by stenm on 17.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>

struct Theme {
  sf::Color UnrevealedCellColor = sf::Color(0x848E99FF);
  sf::Color RevealedCellColor = sf::Color::White;
  sf::Color CellStrokeColor = sf::Color::Black;
  float CellStrokeWidth = -1.f;
  sf::Color TextColor = sf::Color::Black;
  sf::Color MineColor = sf::Color::Red;
  sf::Color MineStrokeColor = sf::Color::Black;
  float MineStrokeWidth = -2.f;
} theme;