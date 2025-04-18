//
// Created by stenm on 17.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Cell.h"

class Game;

class MinesweeperRenderer {
public:
    MinesweeperRenderer(Game* game, sf::RenderTarget* target);
    ~MinesweeperRenderer() = default;

    void render();

private:
    Game* _game;
    sf::RenderTarget* _target;
    sf::Text _text;
    sf::CircleShape _mineShape;
    sf::RectangleShape _cellShape;

    void _renderCell(const Cell& cell, const sf::Vector2f& position);
    void _renderCellContent(const Cell& cell, const sf::Vector2f& position);
    void _renderMine(const sf::Vector2f& position);
    void _renderMineNeighborCount(int neighborMines, const sf::Vector2f& position);
    void _renderEndGameStatus(const std::string& message);
};
