//
// Created by stenm on 16.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Ball.h"

class Game;

class BallUpdater {
public:
    sf::Vector2f gravity{0, 1.f};
    sf::Vector2f wind{10.f, 0};
    float restitution{0.9f};

    explicit BallUpdater(Game* game);

    void update(Ball* ball) const;

private:
    Game* _game;
    void _checkBoundary(Ball* ball) const;
    void _checkBallCollisions(Ball* ball) const;
    static sf::Vector2f _calculateElasticCollision(const Ball* b1, const Ball* b2);
    static sf::Vector2f _calculateElasticCollision(float m1, sf::Vector2f v1, float m2, sf::Vector2f v2);
    static bool _intersects(const Ball* b1, const Ball* b2);
};


