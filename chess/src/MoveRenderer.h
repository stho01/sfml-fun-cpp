//
// Created by stenm on 27.04.2025.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "MoveController.h"

class Game;

class MoveRenderer {
public:
  MoveRenderer(sf::RenderTarget& renderTarget, Game& game);
  ~MoveRenderer() = default;

  void render(const MoveController& moveController);

private:
  sf::RenderTarget& _renderTarget;
  Game& _game;
  sf::RectangleShape _possibleMove{};
  sf::RectangleShape _selectedCell{};

};