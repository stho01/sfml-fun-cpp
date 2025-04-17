//
// Created by stenm on 16.04.2025.
//

#include "BallRenderer.h"


BallRenderer::BallRenderer(sf::RenderTarget* renderTarget) : _renderTarget(renderTarget) {}

void BallRenderer::render(const Ball* ball) {
    auto radius = ball->getSize() / 2;
    _shape.setRadius(radius);
    _shape.setPosition(ball->position);
    _shape.setOrigin({radius, radius});
    _shape.setFillColor(ball->selected ? sf::Color::Green : sf::Color::Cyan);
    _shape.setOutlineColor(sf::Color::Black);
    _shape.setOutlineThickness(-1);
    _renderTarget->draw(_shape);

    sf::Vector2f dir = stho::Vector2f::DOWN;
    if (ball->velocity.lengthSquared() != 0) {
        dir = ball->velocity.normalized();
    }
    _line.p1 = _shape.getPosition();
    _line.p2 = _shape.getPosition() + (dir * radius);


    sf::Vertex vertices[2] = {
        sf::Vertex(_line.p1, sf::Color::Black),
        sf::Vertex(_line.p2, sf::Color::Black)
    };
    _renderTarget->draw(&vertices[0], 2, sf::PrimitiveType::Lines);
}