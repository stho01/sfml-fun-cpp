//
// Created by stho on 23.04.2025.
//

#pragma once

#include "Cell.h"

class Game;

class MoveController {
public:
    explicit MoveController(Game& game);
    ~MoveController();
    Cell* getSelectedCell() const;
    std::optional<std::shared_ptr<Piece>> getSelectedPiece() const;
    std::optional<PieceColor> getSelectedPieceColor() const;
    bool hasSelectedCell() const;
    void setSelectedCell(const sf::Vector2i& position);
    void setSelectedCell(Cell* cell);
    bool moveSelectedPiece(const sf::Vector2i& position);
    bool isSelectedCell(const sf::Vector2i& position) const;
    void deselectCell();
    const std::list<Cell*>& getLegalMoves() const;

private:
    Game& _game;
    Cell* _selectedCell{nullptr};
    std::list<Cell*> _legalMoves{};

    void _setLegalMoves(const Piece& piece);
    void _addPawnMoves(const Piece& piece, std::list<Cell*>& cells) const;
    void _addBishopMoves(const Piece& piece, std::list<Cell*>& cells) const;
    void _addRookMoves(const Piece& piece, std::list<Cell*>& cells) const;
    void _addKnightMoves(const Piece& piece, std::list<Cell*>& cells) const;
    void _addQueenMoves(const Piece& piece, std::list<Cell*>& cells) const;
    void _addKingMoves(const Piece& piece, std::list<Cell*>& cells) const;
    void _getCellsInDirection(const Piece& piece, const sf::Vector2i& direction, std::list<Cell*>& cells) const;
};