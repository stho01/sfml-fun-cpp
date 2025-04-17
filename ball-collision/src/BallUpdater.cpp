//
// Created by stenm on 16.04.2025.
//

#include "BallUpdater.h"
#include "Game.h"
#include <list>

BallUpdater::BallUpdater(Game* game) : _game(game) {}

void BallUpdater::update(Ball* ball) const {
    ball->applyForce(gravity * ball->mass);

    if (isKeyPressed(sf::Keyboard::Key::Space))
        ball->applyForce(wind);

    ball->velocity += ball->acceleration;
    ball->position += ball->velocity * stho::Timer::deltaTimeSeconds();

    _checkBoundary(ball);
    _checkBallCollisions(ball);

    ball->resetAcceleration();
}

void BallUpdater::_checkBoundary(Ball* ball) const {
    auto radius = ball->getSize() / 2;

    if (ball->position.x - radius / 2 < 0)
    {
        ball->position = { radius, ball->position.y };
        ball->velocity = { -ball->velocity.x, ball->velocity.y };
        ball->velocity *= restitution;
    }

    if (ball->position.x + radius > _game->windowWidth())
    {
        ball->position = { _game->windowWidth() - radius, ball->position.y };
        ball->velocity = { -ball->velocity.x, ball->velocity.y };
        ball->velocity *= restitution;
    }

    if (ball->position.y + radius > _game->windowHeight())
    {
        ball->position = { ball->position.x, _game->windowHeight() - radius };
        ball->velocity = { ball->velocity.x, -ball->velocity.y };
        ball->velocity *= restitution;
    }
}

void BallUpdater::_checkBallCollisions(Ball* ball) const {
    // We need to delay mutation of the velocities until after
    // // the elastic collision calculation in order to use the correct variables for
    // // the other ball.
    // std::make_pair
    std::list<std::tuple<Ball*, sf::Vector2f>> updatedVelocities;

    for (const Ball* other: _game->getBalls())
    {
        if (other != ball && _intersects(ball, other))
        {
            auto delta = other->position - ball->position;
            auto deltaNormalized = delta.normalized();
            const auto velocityLength = ball->velocity.length();

            const auto result = _calculateElasticCollision(ball, other);
            ball->velocity.x *= result.x;
            ball->velocity.y *= result.y;

            auto newVelocity = stho::Mathf::reflect(ball->velocity, deltaNormalized) * velocityLength * restitution; // reflect current velocity against other ball

            updatedVelocities.emplace_back(ball, newVelocity);

            const auto overlap = (delta.length() - (ball->getRadius() + other->getRadius())) / 2; // calculate amount of intersection

            ball->position += deltaNormalized * overlap; // set position back to avoid objects to be glued together.
        }
    }

    // We can now update velocities for colliding objects.
    for (auto& tuple : updatedVelocities)
    {
        std::get<0>(tuple)->velocity = std::get<1>(tuple);
    }
}

sf::Vector2f BallUpdater::_calculateElasticCollision(const Ball* b1, const Ball* b2) {
    return _calculateElasticCollision(b1->mass, b1->velocity, b2->mass, b2->velocity);
}

sf::Vector2f BallUpdater::_calculateElasticCollision(const float m1, const sf::Vector2f v1, const float m2, const sf::Vector2f v2) {
    const auto sumM = m1 + m2;
    const auto a = (m1 - m2) / sumM * v1;
    const auto b = 2 * m2 / sumM * v2;
    return a + b;
}

bool BallUpdater::_intersects(const Ball* b1, const Ball* b2) {
    const auto distance = (b2->position - b1->position).lengthSquared();
    const auto r = b1->getRadius() + b2->getRadius();
    return distance <=  r * r;
}