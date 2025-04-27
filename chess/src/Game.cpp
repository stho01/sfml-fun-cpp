//
// Created by stho on 10.04.2025.
//

#include "Game.h"
#include <iostream>
#include "BoardRenderer.h"
#include "MoveController.h"
#include "MoveRenderer.h"

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

    _moveController = std::make_unique<MoveController>(*this);
    _moveRenderer = std::make_unique<MoveRenderer>(*getWindow(), *this);

    _board.setSize({
        windowWidth() * 0.8f,
        windowHeight() * 0.8f
    });
    _board.setPosition(windowCenter() - _board.getSize() / 2.f);

    _board.setup();
}

void Game::update() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (_leftMouseClickedLastFrame) {
            return;
        }

        const auto position = _board.positionFromScreenCoords(getMousePosition());
        if (!_moveController->hasSelectedCell()) {
            _moveController->setSelectedCell(position);

            if (const auto color =  _moveController->getSelectedPieceColor(); color.has_value() && color.value() != _currentPlayer) {
                _moveController->deselectCell();
            }
        } else if (_moveController->isSelectedCell(position)) {
            _moveController->deselectCell();
        } else if (_moveController->moveSelectedPiece(position)) {
            _currentPlayer = _currentPlayer == White ? Black : White;
        }

        _leftMouseClickedLastFrame = true;
    } else {
        _leftMouseClickedLastFrame = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        _board.setup();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        _moveController->deselectCell();
    }
}

void Game::render() {
    _boardRenderer->render(_board);
    _moveRenderer->render(*_moveController);

    for (const auto& cell : _board.getCells()) {
        if (const auto& piece = cell.getPiece(); piece) {
            _pieceRenderer->render(_board, *piece);
        }
    }
}

void Game::unload() {
    std::cout << "Game unloaded!" << std::endl;
}
