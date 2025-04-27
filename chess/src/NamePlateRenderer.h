//
// Created by stenm on 27.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>

class Game;

class NamePlateRenderer {
public:
  NamePlateRenderer(sf::RenderTarget& renderTarget, Game& game);
  ~NamePlateRenderer();

  void render();

private:
  Game& _game;
  sf::RenderTarget& _renderTarget;
  sf::RectangleShape _rectangle;
  sf::Text _currentPlayerName;
  static const std::string WHITE;
  static const std::string BLACK;
};
