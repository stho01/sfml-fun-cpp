//
// Created by stenm on 18.04.2025.
//

#pragma once

#include <extensions/extensions.h>
#include "Piece.h"

class Cell {
public:
    Cell() = default;
    ~Cell() {
        Logger::Info("Destroying Cell");
    }

    Cell(int x, int y) : _position({x,y}) { }

    void setPiece(std::shared_ptr<Piece> piece) {
        _piece = piece;
        if (piece)
            _piece->setPosition(_position);
    }

    bool isEmpty() const {
        return _piece == nullptr;
    }

    const std::shared_ptr<Piece>& getPiece() const {
        return _piece;
    }

    std::shared_ptr<Piece>& getPiece() {
        return _piece;
    }

    bool tryGetPiece(std::shared_ptr<Piece>& piece) const {
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

    void setPosition(int x, int y) {
        _position = {x,y};
    }

    std::string toString() const {
        const auto pieceStr = _piece ? _piece->toString() : "null";
        return "Cell { Pos = { x = " + std::to_string(_position.x) + ", y = " + std::to_string(_position.y) + " } , Piece = " + pieceStr + " }";
    }

private:
    sf::Vector2i _position;
    std::shared_ptr<Piece> _piece{nullptr};
};
