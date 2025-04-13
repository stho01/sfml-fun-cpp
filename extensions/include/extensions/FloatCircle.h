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

        FloatCircle(float x, float y, float radius = 1.0f);
        explicit FloatCircle(sf::Vector2f pos, float radius = 1.0f);

        [[nodiscard]] bool intersects(const FloatCircle& circle) const;
        bool intersects(const FloatCircle& circle, float& intersection) const;
        [[nodiscard]] bool contains(const float& x, const float& y) const;
        [[nodiscard]] bool contains(const sf::Vector2f& point) const;

        explicit operator sf::Vector2f() const {
            return {x, y};
        }
    };
    
}