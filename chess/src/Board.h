//
// Created by stenm on 18.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Cell.h"

class Board {
public:
    Board();

    constexpr static int MAX_TILE_COUNT = 8;
    constexpr static int CELL_COUNT = MAX_TILE_COUNT * MAX_TILE_COUNT;

    const std::array<Cell, CELL_COUNT>& getCells();

    [[nodiscard]] sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);

    [[nodiscard]] sf::Vector2f getSize() const;
    void setSize(const sf::Vector2f& size);

    [[nodiscard]] sf::Vector2f cellSize() const;

    Cell* getCell(int x, int y);
    Cell* getCell(const sf::Vector2i& position);
    bool tryGetCell(const sf::Vector2i& position, Cell*& cell);
    bool tryGetEnemyCell(const sf::Vector2i& position, const PieceColor& color, Cell*& cell);
    bool placePiece(int x, int y, const std::shared_ptr<Piece>& piece);
    [[nodiscard]] sf::IntRect getBoundingBox(int index) const;
    void clear();
    bool movePiece(Cell& sourceCell, Cell& targetCell);
    [[nodiscard]] sf::Vector2i positionFromScreenCoords(const sf::Vector2i& position) const;
    [[nodiscard]] sf::Vector2i positionToScreenCoords(const sf::Vector2i& boardPosition) const;

private:
    std::array<Cell, CELL_COUNT> _cells{};
    sf::Vector2f _position{0,0};
    sf::Vector2f _size{600,600};

    [[nodiscard]] bool _inRange(int value) const;
};
