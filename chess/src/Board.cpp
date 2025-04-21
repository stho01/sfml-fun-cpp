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

bool Board::placePiece(const int x, const int y, const std::shared_ptr<Piece>& piece) {
  auto* cell = getCell(x, y);
  if (cell == nullptr) {
    return false;
  }
  cell->setPiece(piece);
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
    cell.setPiece(nullptr);
  }
}

bool Board::movePiece(Cell& sourceCell, Cell& targetCell) {
  const auto sourcePiece = sourceCell.getPiece();
  const auto targetPiece = targetCell.getPiece();

  if (sourcePiece != nullptr && targetPiece == nullptr) {
    targetCell.setPiece(sourcePiece);
    sourceCell.setPiece(nullptr);
    return true;
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