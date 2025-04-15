//
// Created by stho on 11.04.2025.
//

#include "extensions/FloatCircle.h"
#include <cmath>

stho::FloatCircle::FloatCircle(const float x, const float y, const float radius)
    : x(x), y(y), radius(radius) {}

stho::FloatCircle::FloatCircle(const sf::Vector2f pos, const float radius)
    : x(pos.x), y(pos.y), radius(radius) {}

bool stho::FloatCircle::intersects(const FloatCircle& circle) const {
    const sf::Vector2f pos1 = {circle.x, circle.y};
    const sf::Vector2f pos2 = {x, y};
    const auto lengthSquared = (pos2 - pos1).lengthSquared();
    const auto rSquared = radius * radius + circle.radius * circle.radius;

    return lengthSquared <= rSquared;
}

std::optional<float> stho::FloatCircle::findIntersection(const FloatCircle& circle) const {
    const sf::Vector2f pos1 = {circle.x, circle.y};
    const sf::Vector2f pos2 = {x, y};
    const auto lengthSquared = (pos2 - pos1).lengthSquared();
    const auto rSquared = radius * radius + circle.radius * circle.radius;

    if (lengthSquared <= rSquared) {
        return std::abs(radius + circle.radius - std::sqrt(lengthSquared));
    }
    return std::nullopt;
}

bool stho::FloatCircle::contains(const float& x, const float& y) const {
    return this->intersects({x, y});
}

bool stho::FloatCircle::contains(const sf::Vector2f& point) const {
    return this->intersects({point.x, point.y, 1.0f});
}