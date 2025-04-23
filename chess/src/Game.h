//
// Created by stho on 10.04.2025.
//

#pragma once

#include <extensions/extensions.h>
#include "Board.h"
#include "PieceRenderer.h"

class BoardRenderer;
class MoveController;

class Game final : public stho::GameBase {
public:
    explicit Game(sf::RenderWindow* window);
    ~Game() override;

    void initialize() override;
    void update() override;
    void render() override;
    void unload() override;

    Board& getBoard() { return _board; }

private:
    BoardRenderer* _boardRenderer;
    PieceRenderer* _pieceRenderer;
    std::unique_ptr<MoveController> _moveController{nullptr};
    SpriteAtlas _spriteAtlas;
    Board _board;

    void _setupGame();
};
