//
// Created by stenm on 18.04.2025.
//

#include <extensions/extensions.h>
#include "BoardRenderer.h"
#include "Game.h"

// const std::array<std::string, Board::MAX_TILE_COUNT> BoardRenderer::_numbers = { "1", "2", "3", "4", "5", "6", "7", "8" };
// const std::array<std::string, Board::MAX_TILE_COUNT> BoardRenderer::_letters = { "A", "B", "C", "D", "E", "F", "G", "H" };

BoardRenderer::BoardRenderer(Game& game, sf::RenderTarget& target)
    : _game(game), _target(target), _text(stho::Fonts::Roboto()), _border(), _mouseHover()
{

}

BoardRenderer::~BoardRenderer() {}

void BoardRenderer::initialize() {
    _text.setCharacterSize(14);
    _text.setFillColor(sf::Color::White);

    auto shape = sf::RectangleShape();
    shape.setSize({1.f, 1.f});

    sf::RenderTexture renderTexture({Board::MAX_TILE_COUNT, Board::MAX_TILE_COUNT});

    for (int i = 0; i < 64; i++) {
        int x = i % Board::MAX_TILE_COUNT;
        int y = i / Board::MAX_TILE_COUNT;
        shape.setFillColor(_isDarkTile(x, y) ? sf::Color({0,0,0,100}) : sf::Color({255,255,255,100}));
        shape.setPosition(sf::Vector2f(x, y));
        renderTexture.draw(shape);
    }

    _boardTexture = std::make_unique<sf::Texture>(renderTexture.getTexture());
    _boardSprite = std::make_unique<sf::Sprite>(*_boardTexture);

    // _boardSprite = std::make_unique<sf::Sprite>(renderTexture.getTexture());
}

void BoardRenderer::render(const Board& board) {
    _border.setSize(board.getSize());
    _border.setPosition(board.getPosition());
    _border.setOutlineColor(_borderColor);
    _target.draw(_border);

    if (_boardSprite) {
        _boardSprite->setScale(board.cellSize());
        _boardSprite->setPosition(board.getPosition());
        _target.draw(*_boardSprite);
    }

    auto mousePosition = _game.getMousePosition();
    for (int i = 0; i < 64; i++) {
        auto boundingRect = board.getBoundingBox(i);
        if (!boundingRect.contains(mousePosition))
            continue;

        _mouseHover.setSize(board.cellSize());
        _mouseHover.setPosition(static_cast<sf::Vector2f>(boundingRect.position));
        _mouseHover.setFillColor(_isDarkTile(i) ? sf::Color(0, 0, 0, 100) : sf::Color(255, 255, 255, 100));
        _target.draw(_mouseHover);
        break;
    }

    for (int i = 0; i < Board::MAX_TILE_COUNT; i++) {
        _text.setString(_numbers[i]);
        _text.setPosition(sf::Vector2f(-20, i * board.cellSize().y + (board.cellSize().y / 2.f - _text.getCharacterSize() / 2.f)) + board.getPosition());
        _target.draw(_text);

        _text.setString(_letters[i]);
        _text.setPosition(sf::Vector2f(i * board.cellSize().x + (board.cellSize().x / 2.f - _text.getCharacterSize() / 2.f), board.getSize().y + 10.f) + board.getPosition());
        _target.draw(_text);
    }
}

bool BoardRenderer::_isDarkTile(int x, int y) {
    return (x + y) % 2 == 0;
}

bool BoardRenderer::_isDarkTile(int index) {
    auto x = index % Board::MAX_TILE_COUNT;
    auto y = index / Board::MAX_TILE_COUNT;
    return _isDarkTile(x, y);
}
