//
// Created by stho on 23.04.2025.
//

#include "MoveController.h"
#include "Game.h"
#include "Piece.h"

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

bool MoveController::moveSelectedPiece(const sf::Vector2i& position) {
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

bool MoveController::isSelectedCell(const sf::Vector2i& position) {
    auto cell = _game.getBoard().getCell(position);
    return cell == _selectedCell;
}

void MoveController::deselectCell() {
    _selectedCell = nullptr;
}

std::list<Cell*>& MoveController::_getEligibleCells(const Piece& piece) {
    std::list<Cell*> cells;
    switch (piece.pieceType) {
        case PieceType::Pawn: _addPawnMoves(piece, cells); break;
        case PieceType::Bishop: _addPawnMoves(piece, cells); break;
        case PieceType::King: _addPawnMoves(piece, cells); break;
        case PieceType::Knight: _addPawnMoves(piece, cells); break;
        case PieceType::Queen: _addPawnMoves(piece, cells); break;
        case PieceType::Rook: _addPawnMoves(piece, cells); break;
    }
    return cells;
}

void MoveController::_addPawnMoves(const Piece& piece, std::list<Cell*>& cells) {
    auto& board = _game.getBoard();
    auto yDir = piece.color == PieceColor::Black ? 1 : -1;

    Cell* cell{nullptr};
    if (piece.getMoveCount() == 1 && board.tryGetCell(piece.position + sf::Vector2i(0, yDir * 2), cell) && cell->isEmpty())
        cells.push_back(cell);
    if (board.tryGetCell(piece.position + sf::Vector2i(0, yDir), cell) && cell->isEmpty())
        cells.push_back(cell);
    if (board.tryGetEnemyCell(piece.position + sf::Vector2i(1, yDir), piece.color, cell))
        cells.push_back(cell);
    if (board.tryGetEnemyCell(piece.position + sf::Vector2i(-1, yDir), piece.color, cell))
        cells.push_back(cell);
}

void MoveController::_addBishopMoves(const Piece& piece, std::list<Cell*>& cells) {
    _getCellsInDirection(piece, sf::Vector2i(-1, -1), cells);
    _getCellsInDirection(piece, sf::Vector2i(1, -1), cells);
    _getCellsInDirection(piece, sf::Vector2i(1, 1), cells);
    _getCellsInDirection(piece, sf::Vector2i(-1, 1), cells);
}

void MoveController::_addRookMoves(const Piece& piece, std::list<Cell*>& cells) {
    _getCellsInDirection(piece, sf::Vector2i(0, -1), cells);
    _getCellsInDirection(piece, sf::Vector2i(0, 1), cells);
    _getCellsInDirection(piece, sf::Vector2i(-1, 0), cells);
    _getCellsInDirection(piece, sf::Vector2i(1, 0), cells);
}

void MoveController::_addKnightMoves(const Piece& piece, std::list<Cell*>& cells) {
    auto board = _game.getBoard();

    std::array<Cell*, 8> possibleMoves;
    possibleMoves[0] = board.getCell(piece.position + sf::Vector2i( 1, -2));
    possibleMoves[1] = board.getCell(piece.position + sf::Vector2i( 2, -1));
    possibleMoves[2] = board.getCell(piece.position + sf::Vector2i( 2,  1));
    possibleMoves[3] = board.getCell(piece.position + sf::Vector2i( 1,  2));
    possibleMoves[4] = board.getCell(piece.position + sf::Vector2i(-1,  2));
    possibleMoves[5] = board.getCell(piece.position + sf::Vector2i(-2,  1));
    possibleMoves[6] = board.getCell(piece.position + sf::Vector2i(-2, -1));
    possibleMoves[7] = board.getCell(piece.position + sf::Vector2i(-1, -2));

    for(auto& cell : possibleMoves)
    {
        if (cell == nullptr) continue;
        if (cell->isEmpty() || cell->getPiece()->color != piece.color)
            cells.push_back(cell);
    }
}

void MoveController::_addQueenMoves(const Piece& piece, std::list<Cell*>& cells) {
    _addBishopMoves(piece, cells);
    _addRookMoves(piece, cells);
}

void MoveController::_addKingMoves(const Piece& piece, std::list<Cell*>& cells) {
    auto board = _game.getBoard();

    std::array<Cell*, 8> possibleMoves;
    possibleMoves[0] = board.getCell(piece.position + sf::Vector2i(-1, -1));
    possibleMoves[1] = board.getCell(piece.position + sf::Vector2i( 0, -1));
    possibleMoves[2] = board.getCell(piece.position + sf::Vector2i( 1, -1));
    possibleMoves[3] = board.getCell(piece.position + sf::Vector2i( 1,  0));
    possibleMoves[4] = board.getCell(piece.position + sf::Vector2i( 1,  1));
    possibleMoves[5] = board.getCell(piece.position + sf::Vector2i( 0,  1));
    possibleMoves[6] = board.getCell(piece.position + sf::Vector2i(-1,  1));
    possibleMoves[7] = board.getCell(piece.position + sf::Vector2i(-1,  0));

    for(auto& cell : possibleMoves)
    {
        if (cell == nullptr) continue;
        if (cell->isEmpty() || cell->getPiece()->color != piece.color)
            cells.push_back(cell);
    }
}

void MoveController::_getCellsInDirection(const Piece& piece, const sf::Vector2i& direction, std::list<Cell*>& cells) {
    auto board = _game.getBoard();

    for (auto i = 0; i < Board::MAX_TILE_COUNT; i++)
    {
        auto cell = board.getCell(piece.position + direction * (i+1));

        if (cell == nullptr)
            break;

        if (!cell->isEmpty())
        {
            if (cell->getPiece()->color != piece.color)
                cells.push_back(cell);

            break;
        }

        cells.push_back(cell);
    }
}
