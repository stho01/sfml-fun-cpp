//
// Created by stenm on 17.04.2025.
//

#include "Cell.h"

Cell::Cell(const int x, const int y)
    : _x(x), _y(y), _isMine(false), _isRevealed(false) {}

int Cell::x() const {
    return _x;
}
int Cell::y() const {
    return _y;
}
bool Cell::isMine() const {
    return _isMine;
}
bool Cell::isRevealed() const {
    return _isRevealed;
}
void Cell::setRevealed() {
    _isRevealed = true;
}
void Cell::setMine(const bool mine) {
    _isMine = mine;
}
int Cell::getNeighborMines() const {
  return _isMine ? -1 : _neighborMines;
}
void Cell::setNeighborMines(const int neighborMines) {
  _neighborMines = neighborMines;
}
void Cell::addOneToNeighborMines()  {
    _neighborMines++;
}