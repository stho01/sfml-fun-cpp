//
// Created by stenm on 18.04.2025.
//

#pragma once

#include "Piece.h"

class Cell {
public:
    Cell() = default;
    Cell(int x, int y) : _position({x,y}) { }

    void setPiece(Piece* piece) {
        _piece = piece;
        if (piece)
            _piece->setPosition(_position);
    }

    bool isEmpty() const {
        return _piece == nullptr;
    }

    Piece* getPiece() const {
        return _piece;
    }

    bool tryGetPiece(Piece*& piece) const {
        piece = nullptr;
        if (_piece != nullptr) {
            piece = _piece;
            return true;
        }
        return false;
    }

    sf::Vector2i getPosition() const {
        return _position;
    }

    std::string toString() const {
        const auto pieceStr = _piece ? _piece->toString() : "null";
        return "Cell { Pos = { x = " + std::to_string(_position.x) + ", y = " + std::to_string(_position.y) + " } , Piece = " + pieceStr + " }";
    }

private:
    sf::Vector2i _position;
    Piece* _piece{nullptr};
};
