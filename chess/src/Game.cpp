//
// Created by stho on 10.04.2025.
//

#include <iostream>
#include "Game.h"
#include "BoardRenderer.h"

Game::Game(sf::RenderWindow* window)
    : GameBase(window)
      , _boardRenderer(nullptr) {
    window->setFramerateLimit(30);
}

Game::~Game() {
    delete _boardRenderer;
}

void Game::initialize() {
    Logger::Info("Initialized sprites");

    _spriteAtlas.load("assets/chess2.atlas.json");

    setClearColor(sf::Color(0x21100EFF));
    _boardRenderer = new BoardRenderer(*this, *getWindow());
    _boardRenderer->initialize();

    _pieceRenderer = new PieceRenderer(*getWindow(), _spriteAtlas);
    _pieceRenderer->initialize();

    _board.setSize({
        windowWidth() * 0.8f,
        windowHeight() * 0.8f
    });
    _board.setPosition(windowCenter() - _board.getSize() / 2.f);

    _setupGame();
}

void Game::update() {
    // Logger::Info(std::format("Delta Time: {:.13f} seconds", static_cast<float>(stho::Timer::getDeltaTimeSeconds())));
}

void Game::render() {
    _boardRenderer->render(_board);

    for (const auto& cell : _board.getCells()) {
        if (const auto& piece = cell.getPiece(); piece) {
            _pieceRenderer->render(_board, *piece);
        }
    }
}

void Game::unload() {
    std::cout << "Game unloaded!" << std::endl;
}

void Game::_setupGame() {
    _board.clear();
    _board.placePiece(0, 0, std::make_shared<Piece>(Rook, Black));
    _board.placePiece(1, 0, std::make_shared<Piece>(Knight, Black));
    _board.placePiece(2, 0, std::make_shared<Piece>(Bishop, Black));
    _board.placePiece(3, 0, std::make_shared<Piece>(Queen, Black));
    _board.placePiece(4, 0, std::make_shared<Piece>(King, Black));
    _board.placePiece(5, 0, std::make_shared<Piece>(Bishop, Black));
    _board.placePiece(6, 0, std::make_shared<Piece>(Knight, Black));
    _board.placePiece(7, 0, std::make_shared<Piece>(Rook, Black));

    for (int i = 0; i < Board::MAX_TILE_COUNT; i++)
    {
        _board.placePiece(i, 1, std::make_shared<Piece>(Pawn, Black));
        _board.placePiece(i, 6, std::make_shared<Piece>(Pawn, White));
    }

    _board.placePiece(0, 7, std::make_shared<Piece>(Rook, White));
    _board.placePiece(1, 7, std::make_shared<Piece>(Knight, White));
    _board.placePiece(2, 7, std::make_shared<Piece>(Bishop, White));
    _board.placePiece(3, 7, std::make_shared<Piece>(Queen, White));
    _board.placePiece(4, 7, std::make_shared<Piece>(King, White));
    _board.placePiece(5, 7, std::make_shared<Piece>(Bishop, White));
    _board.placePiece(6, 7, std::make_shared<Piece>(Knight, White));
    _board.placePiece(7, 7, std::make_shared<Piece>(Rook, White));
}
