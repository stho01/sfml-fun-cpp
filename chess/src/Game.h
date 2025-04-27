//
// Created by stho on 10.04.2025.
//

#pragma once

#include <extensions/extensions.h>
#include "Board.h"
#include "PieceRenderer.h"

class BoardRenderer;
class MoveController;
class MoveRenderer;
class NamePlateRenderer;

class Game final : public stho::GameBase {
public:
    explicit Game(sf::RenderWindow* window);
    ~Game() override;

    void initialize() override;
    void update() override;
    void render() override;
    void unload() override;

    Board& getBoard() { return _board; }
    const PieceColor& getCurrentPlayer() const { return _currentPlayer; }

private:
    std::unique_ptr<BoardRenderer> _boardRenderer;
    std::unique_ptr<PieceRenderer> _pieceRenderer;
    std::unique_ptr<MoveController> _moveController{nullptr};
    std::unique_ptr<MoveRenderer> _moveRenderer{nullptr};
    std::unique_ptr<NamePlateRenderer> _namePlateRenderer{nullptr};
    SpriteAtlas _spriteAtlas;
    Board _board;
    bool _leftMouseClickedLastFrame{false};
    PieceColor _currentPlayer{White};

};
