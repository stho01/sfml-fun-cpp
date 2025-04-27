//
// Created by stenm on 18.04.2025.
//

#include "Board.h"

Board::Board() {
  for (auto x = 0; x < MAX_TILE_COUNT; x++) {
    for (auto y = 0; y < MAX_TILE_COUNT; y++) {
      const auto i = y * MAX_TILE_COUNT + x;
      _cells[i] = Cell(x, y);
    }
  }
}

void Board::setup() {
  clear();

  placePiece(0, 0, _piecePool.acquire(Rook, Black));
  placePiece(1, 0, _piecePool.acquire(Knight, Black));
  placePiece(2, 0, _piecePool.acquire(Bishop, Black));
  placePiece(3, 0, _piecePool.acquire(Queen, Black));
  placePiece(4, 0, _piecePool.acquire(King, Black));
  placePiece(5, 0, _piecePool.acquire(Bishop, Black));
  placePiece(6, 0, _piecePool.acquire(Knight, Black));
  placePiece(7, 0, _piecePool.acquire(Rook, Black));

  for (int i = 0; i < MAX_TILE_COUNT; i++)
  {
    placePiece(i, 1, _piecePool.acquire(Pawn, Black));
    placePiece(i, 6, _piecePool.acquire(Pawn, White));
  }

  placePiece(0, 7, _piecePool.acquire(Rook, White));
  placePiece(1, 7, _piecePool.acquire(Knight, White));
  placePiece(2, 7, _piecePool.acquire(Bishop, White));
  placePiece(3, 7, _piecePool.acquire(Queen, White));
  placePiece(4, 7, _piecePool.acquire(King, White));
  placePiece(5, 7, _piecePool.acquire(Bishop, White));
  placePiece(6, 7, _piecePool.acquire(Knight, White));
  placePiece(7, 7, _piecePool.acquire(Rook, White));
}


const std::array<Cell, Board::CELL_COUNT>& Board::getCells() {
  return _cells;
}

sf::Vector2f Board::getPosition() const {
  return _position;
}

void Board::setPosition(const sf::Vector2f& position) {
  _position = position;
}

sf::Vector2f Board::getSize() const {
  return _size;
}

void Board::setSize(const sf::Vector2f& size) {
  _size = size;
}

sf::Vector2f Board::cellSize() const {
  return {_size.x / MAX_TILE_COUNT, _size.y / MAX_TILE_COUNT};
}

Cell* Board::getCell(int x, int y) {
  if (_inRange(x) && _inRange(y)) {
    const int index = x + y * MAX_TILE_COUNT;
    return &_cells[index];
  }
  return nullptr;
}

Cell* Board::getCell(const sf::Vector2i& position) {
  return getCell(position.x, position.y);
}

bool Board::tryGetCell(const sf::Vector2i& position, Cell*& cell) {
  cell = getCell(position.x, position.y);
  return cell != nullptr;
}

bool Board::tryGetEnemyCell(const sf::Vector2i& position, const PieceColor& color, Cell*& cell) {
  cell = getCell(position);
  if (cell == nullptr) {
    return false;
  }
  const auto piece = cell->getPiece();
  return piece && piece->color != color;
}

bool Board::placePiece(const int x, const int y, Piece* piece) {
  if (auto* cell = getCell(x, y)) {
    cell->setPiece(piece);
    return true;
  }
  return true;
}

sf::IntRect Board::getBoundingBox(int index) const {
  int x = index % MAX_TILE_COUNT;
  int y = index / MAX_TILE_COUNT;

  if (!_inRange(x) || !_inRange(y)) {
    throw std::out_of_range("Index out of range");
  }

  auto sizeX = static_cast<int>(x * cellSize().x + _position.x);
  auto sizeY = static_cast<int>(y * cellSize().y + _position.y);
  auto cellSizeX = static_cast<int>(cellSize().x);
  auto cellSizeY = static_cast<int>(cellSize().y);

  return {
      { sizeX, sizeY },
      { cellSizeX, cellSizeY }
  };
}

void Board::clear() {
  for (auto& cell : _cells) {
    if (auto* piece = cell.getPiece()) {
      _piecePool.release(piece);
    }
    cell.setPiece(nullptr);
  }
}

bool Board::movePiece(Cell& sourceCell, Cell& targetCell) {
  if (sourceCell.isEmpty() == false) {
    if (targetCell.isEmpty()) {
      targetCell.setPiece(sourceCell.getPiece());
      sourceCell.setPiece(nullptr);
      return true;
    }
    // If the target cell is not empty, check if the piece is an enemy
    if (Piece* piece; targetCell.tryGetPiece(piece) && piece->color != sourceCell.getPiece()->color) {
      targetCell.setPiece(sourceCell.getPiece());
      sourceCell.setPiece(nullptr);
      _piecePool.release(piece); // Piece died. Release the captured piece
      return true;
    }
  }
  return false;
}

sf::Vector2i Board::positionFromScreenCoords(const sf::Vector2i& screenCoords) const {
  auto xn = static_cast<int>((screenCoords.x - _position.x) / _size.x * MAX_TILE_COUNT);
  auto yn = static_cast<int>((screenCoords.y - _position.y) / _size.y * MAX_TILE_COUNT);
  return { xn, yn };
}

sf::Vector2i Board::positionToScreenCoords(const sf::Vector2i& boardPosition) const {
  auto xn = static_cast<int>(boardPosition.x / 8.f * _size.x + _position.x);
  auto yn = static_cast<int>(boardPosition.y / 8.f * _size.y + _position.y);
  return { xn, yn };
}

bool Board::_inRange(const int value) const {
  return value >= 0 && value < MAX_TILE_COUNT;
}