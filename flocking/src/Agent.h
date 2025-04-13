//
// Created by stho on 12.04.2025.
//
#pragma once

#include <SFML/System.hpp>

struct Agent {
    float speed = 150.0f; // 20px pr sec
    float size = 12.0f;
    sf::Vector2f pos;
    sf::Vector2f acceleration;
    sf::Vector2f velocity;
    float neighborhoodRadius = 72.0f;
};