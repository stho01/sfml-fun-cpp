//
// Created by stho on 11.04.2025.
//

#pragma once

#include <SFML/System.hpp>

namespace stho {

    class FloatCircle
    {
    public:
        float x;
        float y;
        float radius;

        FloatCircle(const float x, const float y, const float radius = 1.0f)
            : x(x), y(y), radius(radius) {}

        explicit FloatCircle(const sf::Vector2f pos, const float radius = 1.0f)
            : x(pos.x), y(pos.y), radius(radius) {}

        bool intersects(const FloatCircle& circle) const;
        bool intersects(const FloatCircle& circle, float& intersection) const;
        bool contains(const float& x, const float& y) const;

        operator sf::Vector2f() const {
            return sf::Vector2f(x, y);
        }
    };
    
}