//
// Created by stho on 10.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <extensions/extensions.h>
#include "Ball.h"
#include "BallRenderer.h"

class BallUpdater;

class Game final : public stho::GameBase {
public:
    explicit Game(sf::RenderWindow* window);
    ~Game() override;

    void initialize() override;
    void update() override;
    void render() override;
    void unload() override;

    const std::vector<Ball*>& getBalls() const {
        return _balls;
    }

private:
    std::vector<Ball*> _balls;
    Ball* _selected{nullptr};
    BallRenderer* _ballRenderer;
    BallUpdater* _ballUpdater;
    const int _numberOfBalls{12};

    void _updateSelectedBallState();
    Ball* _getBallFromPoint(int x, int y) const;
};
