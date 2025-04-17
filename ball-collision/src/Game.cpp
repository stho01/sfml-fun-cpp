//
// Created by stho on 10.04.2025.
//

#include <iostream>
#include "Game.h"
#include "BallUpdater.h"

Game::Game(sf::RenderWindow* window): GameBase(window) {
    setClearColor(sf::Color::Black);
}

Game::~Game() {
    delete _ballRenderer;
    delete _ballUpdater;
}

void Game::initialize() {
    Logger::Info("Initialized sprites");

    _ballRenderer = new BallRenderer(this->m_window);
    _ballUpdater = new BallUpdater(this);

    for (auto i = 0; i < _numberOfBalls; i++) {
        auto b = new Ball();
        b->position = {
            50.f + i * 100.f,
            100.f
        };
        b->mass = stho::RandomNumber::nextFloat(10.0f, 50.0f);
        _balls.push_back(b);
    }
}

void Game::update() {
    _updateSelectedBallState();
    for (Ball* ball : _balls) {
        _ballUpdater->update(ball);
    }

    if (isKeyPressed(sf::Keyboard::Key::R)) {
        for (auto i = 0; i < _balls.size(); i++) {
            _balls[i]->position = {50.f + i * 100.f, 100.f};
            _balls[i]->velocity = {0.f, 0.f};
        }
    }
}

void Game::render() {
    for (const Ball* ball : _balls) {
        _ballRenderer->render(ball);
    }

    if (_selected != nullptr) {
        const auto p1 = static_cast<sf::Vector2f>(getMousePosition());
        const auto p2 = _selected->position;

        const sf::Vertex vertices[2] = {
            sf::Vertex(p1, sf::Color::Magenta),
            sf::Vertex(p2, sf::Color::Magenta)
        };

        m_window->draw(&vertices[0], 2, sf::PrimitiveType::Lines);
    }
}

void Game::unload() {
    std::cout << "Game unloaded!" << std::endl;
}

void Game::_updateSelectedBallState() {
    if (isButtonPressed(sf::Mouse::Button::Left)) {
        const auto mousePos = getMousePosition();

        if (_selected == nullptr) {
            if (const auto selected = _getBallFromPoint(mousePos.x, mousePos.y); selected != nullptr) {
                _selected = selected;
                selected->select();
            }
        } else {
            const auto delta = (static_cast<sf::Vector2f>(mousePos) - _selected->position);
            _selected->applyForce(delta);
        }
    } else {
        if (_selected != nullptr) {
            _selected->unselect();
            _selected = nullptr;
        }
    }
}

Ball* Game::_getBallFromPoint(const int x, const int y) const {
    for (Ball* ball : _balls) {
        if (stho::FloatCircle circle(ball->position, ball->getRadius()); circle.contains(x, y)) {
            return ball;
        }
    }
    return nullptr;
}
