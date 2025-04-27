//
// Created by stho on 23.04.2025.
//

#include "MoveController.h"
#include "Game.h"
#include "Piece.h"

MoveController::MoveController(Game& game)
    : _game(game) {}

MoveController::~MoveController() {
    Logger::Info("MoveController destroyed");
}


Cell* MoveController::getSelectedCell() const {
    return _selectedCell;
}

Piece* MoveController::getSelectedPiece() const {
    if (_selectedCell != nullptr) {
        return _selectedCell->getPiece();
    }
    return nullptr;
}

std::optional<PieceColor> MoveController::getSelectedPieceColor() const {
    auto* piece = getSelectedPiece();
    if (piece != nullptr) {
        return piece->color;
    }
    return std::nullopt;
}

bool MoveController::hasSelectedCell() const {
    return _selectedCell != nullptr;
}

void MoveController::setSelectedCell(const sf::Vector2i& position) {
    auto* cell = _game.getBoard().getCell(position);
    if (!cell) {
        return;
    }
    if (cell->isEmpty()) {
        return;
    }
    setSelectedCell(cell);
}

void MoveController::setSelectedCell(Cell* cell) {
    _selectedCell = cell;
    if (cell != nullptr) {
        Logger::Info("Selected cell {}", cell->toString());
        if (const auto* piece = cell->getPiece()) {
            _setLegalMoves(*piece);
        } else {
            _legalMoves.clear();
        }
    }
}

bool MoveController::moveSelectedPiece(const sf::Vector2i& position) {
    if (_legalMoves.empty()) {
        return false;
    }

    bool canMove = false;
    for (const auto& cell : _legalMoves) {
        if (cell->getPosition() == position) {
            canMove = true;
            break;
        }
    }
    if (!canMove) {
        return false;
    }

    auto& board = _game.getBoard();
    if (auto* cell = board.getCell(position); board.movePiece(*_selectedCell, *cell)) {
        _selectedCell = nullptr;
        _legalMoves.clear();
        return true;
    }

    return false;
}

bool MoveController::isSelectedCell(const sf::Vector2i& position) const {
    const auto* cell = _game.getBoard().getCell(position);
    return cell == _selectedCell;
}

void MoveController::deselectCell() {
    _selectedCell = nullptr;
    _legalMoves.clear();
}

const std::list<Cell*>& MoveController::getLegalMoves() const {
    return _legalMoves;
}

void MoveController::_setLegalMoves(const Piece& piece) {
    _legalMoves.clear();
    switch (piece.pieceType) {
        case Pawn: _addPawnMoves(piece, _legalMoves); break;
        case Bishop: _addBishopMoves(piece, _legalMoves); break;
        case King: _addKingMoves(piece, _legalMoves); break;
        case Knight: _addKnightMoves(piece, _legalMoves); break;
        case Queen: _addQueenMoves(piece, _legalMoves); break;
        case Rook: _addRookMoves(piece, _legalMoves); break;
    }
}

void MoveController::_addPawnMoves(const Piece& piece, std::list<Cell*>& cells) const {
    auto& board = _game.getBoard();
    const auto yDir = piece.color == Black ? 1 : -1;

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

void MoveController::_addBishopMoves(const Piece& piece, std::list<Cell*>& cells) const {
    _getCellsInDirection(piece, sf::Vector2i(-1, -1), cells);
    _getCellsInDirection(piece, sf::Vector2i(1, -1), cells);
    _getCellsInDirection(piece, sf::Vector2i(1, 1), cells);
    _getCellsInDirection(piece, sf::Vector2i(-1, 1), cells);
}

void MoveController::_addRookMoves(const Piece& piece, std::list<Cell*>& cells) const {
    _getCellsInDirection(piece, sf::Vector2i(0, -1), cells);
    _getCellsInDirection(piece, sf::Vector2i(0, 1), cells);
    _getCellsInDirection(piece, sf::Vector2i(-1, 0), cells);
    _getCellsInDirection(piece, sf::Vector2i(1, 0), cells);
}

void MoveController::_addKnightMoves(const Piece& piece, std::list<Cell*>& cells) const {
    auto& board = _game.getBoard();

    std::array<Cell*, 8> possibleMoves{};
    possibleMoves[0] = board.getCell(piece.position + sf::Vector2i( 1, -2));
    possibleMoves[1] = board.getCell(piece.position + sf::Vector2i( 2, -1));
    possibleMoves[2] = board.getCell(piece.position + sf::Vector2i( 2,  1));
    possibleMoves[3] = board.getCell(piece.position + sf::Vector2i( 1,  2));
    possibleMoves[4] = board.getCell(piece.position + sf::Vector2i(-1,  2));
    possibleMoves[5] = board.getCell(piece.position + sf::Vector2i(-2,  1));
    possibleMoves[6] = board.getCell(piece.position + sf::Vector2i(-2, -1));
    possibleMoves[7] = board.getCell(piece.position + sf::Vector2i(-1, -2));

    for (auto& cell : possibleMoves)
    {
        if (cell == nullptr) continue;
        if (cell->isEmpty() || cell->getPiece()->color != piece.color)
            cells.push_back(cell);
    }
}

void MoveController::_addQueenMoves(const Piece& piece, std::list<Cell*>& cells) const {
    _addBishopMoves(piece, cells);
    _addRookMoves(piece, cells);
}

void MoveController::_addKingMoves(const Piece& piece, std::list<Cell*>& cells) const {
    auto& board = _game.getBoard();

    std::array<Cell*, 8> possibleMoves{};
    possibleMoves[0] = board.getCell(piece.position + sf::Vector2i(-1, -1));
    possibleMoves[1] = board.getCell(piece.position + sf::Vector2i( 0, -1));
    possibleMoves[2] = board.getCell(piece.position + sf::Vector2i( 1, -1));
    possibleMoves[3] = board.getCell(piece.position + sf::Vector2i( 1,  0));
    possibleMoves[4] = board.getCell(piece.position + sf::Vector2i( 1,  1));
    possibleMoves[5] = board.getCell(piece.position + sf::Vector2i( 0,  1));
    possibleMoves[6] = board.getCell(piece.position + sf::Vector2i(-1,  1));
    possibleMoves[7] = board.getCell(piece.position + sf::Vector2i(-1,  0));

    for (auto& cell : possibleMoves) {
        if (cell == nullptr)
            continue;

        if (cell->isEmpty() || cell->getPiece()->color != piece.color)
            cells.push_back(cell);
    }
}

void MoveController::_getCellsInDirection(const Piece& piece, const sf::Vector2i& direction, std::list<Cell*>& cells) const {
    auto& board = _game.getBoard();

    for (auto i = 0; i < Board::MAX_TILE_COUNT; i++)
    {
        auto* cell = board.getCell(piece.position + direction * (i+1));

        if (cell == nullptr)
            break;

        if (cell->isEmpty() == false) {
            if (cell->getPiece()->color != piece.color)
                cells.push_back(cell);

            break;
        }

        cells.push_back(cell);
    }
}
