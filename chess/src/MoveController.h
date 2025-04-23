//
// Created by stho on 23.04.2025.
//

#pragma once

#include "Cell.h"

class Game;

class MoveController {
public:
    explicit MoveController(Game& game);
    ~MoveController() = default;
    Cell* getSelectedCell();
    void setSelectedCell(const sf::Vector2i& position);
    void setSelectedCell(Cell* cell);
    bool moveSelectedPiece(const sf::Vector2i& position);
    bool isSelectedCell(const sf::Vector2i& position);
    void deselectCell();

private:
    Game& _game;
    Cell* _selectedCell{nullptr};
    std::optional<std::list<Cell*>> _eligibleCells{std::nullopt};

    const std::list<Cell&>& _getEligibleCells(const Piece& piece);
    void _addPawnMoves(const Piece& piece, std::list<Cell&>& cells);
    void _addBishopMoves(const Piece& piece, std::list<Cell&>& cells);
    void _addRookMoves(const Piece& piece, std::list<Cell&>& cells);
    void _addKnightMoves(const Piece& piece, std::list<Cell&>& cells);
    void _addQueenMoves(const Piece& piece, std::list<Cell&>& cells);
    void _addKingMoves(const Piece& piece, std::list<Cell&>& cells);
    void _getCellsInDirection(const Piece& piece, const sf::Vector2i& direction);
};