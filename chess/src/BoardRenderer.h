//
// Created by stenm on 18.04.2025.
//

#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include "Board.h"

class Game;

class BoardRenderer {
public:
    BoardRenderer(Game& game, sf::RenderTarget& target);
    ~BoardRenderer();

    void initialize();
    void render(const Board& board);

private:
    Game& _game;
    sf::RenderTarget& _target;
    sf::Text _text;
    std::unique_ptr<sf::Texture> _boardTexture{nullptr};
    std::unique_ptr<sf::Sprite> _boardSprite{nullptr};
    sf::Color _borderColor{0x2C1604FF};
    sf::Color _darkColor{0x683914FF};
    sf::Color _lightColor{sf::Color::White};
    sf::RectangleShape _border;
    sf::RectangleShape _mouseHover;
    std::array<std::string, Board::MAX_TILE_COUNT> _numbers{ "1", "2", "3", "4", "5", "6", "7", "8" };
    std::array<std::string, Board::MAX_TILE_COUNT> _letters{ "A", "B", "C", "D", "E", "F", "G", "H" };

    bool _isDarkTile(int x, int y);
    bool _isDarkTile(int index);
};
