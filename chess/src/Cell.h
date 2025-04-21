//
// Created by stenm on 18.04.2025.
//

#pragma once

#include "Piece.h"

class Cell {
public:
    Cell() = default;
    Cell(int x, int y) : _position({x,y}) { }

    void setPiece(const std::shared_ptr<Piece>& piece) {
        _piece = piece;
        if (piece)
            _piece->setPosition(_position);
    }

    const std::shared_ptr<Piece>& getPiece() const {
        return _piece;
    }

    sf::Vector2i getPosition() const {
        return _position;
    }

    std::string toString() const {
        auto pieceStr = _piece ? _piece->toString() : "null";
        return "Cell { Pos = { x = " + std::to_string(_position.x) + ", y = " + std::to_string(_position.y) + " } , Piece = " + pieceStr + " }";
    }

private:
    sf::Vector2i _position;
    std::shared_ptr<Piece> _piece{nullptr};
};
