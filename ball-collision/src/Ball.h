//
// Created by stenm on 16.04.2025.
//

#pragma once
#include <SFML/System/Vector2.hpp>

struct Ball {
    float mass{1};
    sf::Vector2f acceleration{0, 0};
    sf::Vector2f velocity{0, 0};
    sf::Vector2f position{0, 0};
    bool selected{false};

    float getSize() const { return mass * 2; }
    float getRadius() const { return mass; }

    void applyForce(const sf::Vector2f& force) {
        acceleration += force / mass;
    }

    void resetAcceleration() {
        acceleration = {0, 0};
    }

    void select() { selected = true; }
    void unselect() { selected = false; }
};
