//
// Created by stenm on 18.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>

enum PieceColor : int {
    White = 0,
    Black
};

enum PieceType : int {
    Pawn = 0,
    Bishop,
    Knight,
    Rook,
    Queen,
    King
};

namespace std {
    template <>
    struct hash<std::pair<PieceType, PieceColor>> {
        std::size_t operator()(const std::pair<PieceType, PieceColor>& p) const noexcept {
            return (static_cast<int>(p.first) << 1) ^ static_cast<int>(p.second);
        }
    };
}

struct Piece {

    Piece(const PieceType type, const PieceColor color)
        : position({0,0}), pieceType(type), color(color), _moveCounter(0) {}

    sf::Vector2i position;
    PieceType pieceType;
    PieceColor color;
    int getMoveCount() const { return _moveCounter; }

    void setPosition(const sf::Vector2i newPosition) {
        position = newPosition;
        _moveCounter++;
    }

    std::string toString() const {
        return "{"
               " Type = " + std::to_string(pieceType) +
               ", Color = " + std::to_string(color) +
               ", Position = { x = " + std::to_string(position.x) +
               ", y = " + std::to_string(position.y) + " }" +
               "}";
    }

private:
  int _moveCounter;
};