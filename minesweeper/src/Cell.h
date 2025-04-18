//
// Created by stenm on 17.04.2025.
//

#pragma once

class Cell {
public:
  Cell(int x, int y);

  [[nodiscard]] int x() const;
  [[nodiscard]] int y() const;
  [[nodiscard]] bool isMine() const;
  [[nodiscard]] bool isRevealed() const;
  void setRevealed();
  void setMine(bool mine);
  int getNeighborMines() const;
  void setNeighborMines(int neighborMines);
  void addOneToNeighborMines();

private:
  int _x;
  int _y;
  bool _isMine;
  bool _isRevealed;
  int _neighborMines{0};
};