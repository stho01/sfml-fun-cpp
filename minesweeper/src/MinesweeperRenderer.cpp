//
// Created by stenm on 17.04.2025.
//

#include "MinesweeperRenderer.h"
#include "Game.h"
#include "Theme.h"

MinesweeperRenderer::MinesweeperRenderer(Game* game, sf::RenderTarget* target)
    : _game(game), _target(target), _text(stho::Fonts::Roboto()) {
    _mineShape.setOutlineThickness(-2);
    _mineShape.setOutlineColor(theme.MineStrokeColor);
}

void MinesweeperRenderer::render() {
    _cellShape.setSize(static_cast<sf::Vector2f>(_game->getCellSize()));

    for (const auto& cell : _game->getCells()) {
        const auto x = cell.x();
        const auto y = cell.y();

        const sf::Vector2f position = {
            x * _cellShape.getSize().x,
            y * _cellShape.getSize().y
        };
        _renderCell(cell, position);
        _renderCellContent(cell, position);
    }

    if (_game->isGameOver()) {
        _renderEndGameStatus(_game->getGameStatus());
    }
}

void MinesweeperRenderer::_renderCell(const Cell& cell, const sf::Vector2f& position) {
    _cellShape.setSize(static_cast<sf::Vector2f>(_game->getCellSize()));
    _cellShape.setFillColor(cell.isRevealed() ? theme.RevealedCellColor : theme.UnrevealedCellColor);
    _cellShape.setOutlineThickness(theme.CellStrokeWidth);
    _cellShape.setOutlineColor(theme.CellStrokeColor);
    _cellShape.setPosition(position);
    _target->draw(_cellShape);
}

void MinesweeperRenderer::_renderCellContent(const Cell& cell, const sf::Vector2f& position) {
    if (!cell.isRevealed())
        return;

    if (cell.isMine())
    {
        _renderMine(position);
        return;
    }

    if (cell.getNeighborMines() > 0)
        _renderMineNeighborCount(cell.getNeighborMines(), position);
}

void MinesweeperRenderer::_renderMine(const sf::Vector2f& position) {
    const auto cellSize = static_cast<sf::Vector2f>(_game->getCellSize());
    _mineShape.setRadius((std::min(cellSize.x, cellSize.y) * 0.25f));
    _mineShape.setOrigin(sf::Vector2f(_mineShape.getRadius(), _mineShape.getRadius()));
    _mineShape.setPosition(position + cellSize / 2.f);
    _mineShape.setFillColor(theme.MineColor);
    _mineShape.setOutlineColor(theme.MineStrokeColor);
    _mineShape.setOutlineThickness(theme.MineStrokeWidth);
    _target->draw(_mineShape);
}

void MinesweeperRenderer::_renderMineNeighborCount(const int neighborMines, const sf::Vector2f& position) {
    const auto cellSize = static_cast<sf::Vector2f>(_game->getCellSize());
    _text.setString(std::to_string(neighborMines));
    _text.setFillColor(theme.TextColor);
    _text.setCharacterSize(static_cast<int>(cellSize.y * 0.8f));
    _text.setOrigin({ cellSize.x / 2.f, _cellShape.getSize().y / 2.f });
    _text.setPosition({
        (position.x + cellSize.x / 2.f) + _text.getLocalBounds().size.x,
        position.y + cellSize.y / 2.f
    });
    _target->draw(_text);
}

void MinesweeperRenderer::_renderEndGameStatus(const std::string& message) {
    auto overlay = sf::RectangleShape(static_cast<sf::Vector2f>(_target->getSize()));
    overlay.setFillColor(sf::Color(0x000000AA));
    _target->draw(overlay);

    auto text = sf::Text(stho::Fonts::Roboto(), message);
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::White);

    const auto bounds = text.getLocalBounds();

    text.setPosition({
        _game->windowWidth() / 2.f - bounds.size.x / 2.f,
        _game->windowHeight() / 2.f - bounds.size.y / 2.f
    });

    _target->draw(text);
}
