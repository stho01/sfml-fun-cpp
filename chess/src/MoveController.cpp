//
// Created by stho on 23.04.2025.
//

#include "MoveController.h"
#include "Game.h"

MoveController::MoveController(Game& game)
    : _game(game) {}

Cell* MoveController::getSelectedCell() {
    return _selectedCell;
}

void MoveController::setSelectedCell(const sf::Vector2i& position) {
    auto cell = _game.getBoard().getCell(position);
    if (!cell) {
        return;
    }
    if (cell->isEmpty()) {
        return;
    }
    _selectedCell = cell;
}

void MoveController::setSelectedCell(Cell* cell) {

}

bool MoveController::moveSelectedPiece(sf::Vector2i position) {
    if (!_eligibleCells.has_value()) {
        return false;
    }
    bool canMove = false;
    for (const auto& cell : *_eligibleCells) {
        if (cell->getPosition() == position) {
            canMove = true;
            break;
        }
    }
    if (!canMove) {
        return false;
    }

    auto cell = _game.getBoard().getCell(position);
    if (_game.getBoard().movePiece(*_selectedCell, *cell)) {
        _selectedCell    = nullptr;
        _eligibleCells = std::nullopt;
        return true;
    }
}

bool MoveController::isSelectedCell(sf::Vector2i position) {

}

void MoveController::deselectCell() {

}

const std::list<Cell&>& MoveController::_getEligibleCells(const Piece& piece) {

}

void MoveController::_addPawnMoves(const Piece& piece, std::list<Cell&>& cells) {

}

void MoveController::_addBishopMoves(const Piece& piece, std::list<Cell&>& cells) {

}

void MoveController::_addRookMoves(const Piece& piece, std::list<Cell&>& cells) {

}

void MoveController::_addKnightMoves(const Piece& piece, std::list<Cell&>& cells) {

}

void MoveController::_addQueenMoves(const Piece& piece, std::list<Cell&>& cells) {

}

void MoveController::_addKingMoves(const Piece& piece, std::list<Cell&>& cells) {

}

void MoveController::_getCellsInDirection(const Piece& piece, const sf::Vector2i& direction) {

}
