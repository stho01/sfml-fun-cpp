//
// Created by stho on 11.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "FloatCircle.h"

namespace stho {

    class FloatLine
    {
    public:
        sf::Vector2f p1;
        sf::Vector2f p2;

        FloatLine(float x1, float y1, float x2, float y2);
        FloatLine(sf::Vector2f p1, sf::Vector2f p2);

        bool intersects(const FloatLine& line, sf::Vector2f& intersection) const;
        bool intersects(const FloatCircle& circle, std::vector<sf::Vector2f>& intersections) const;

        [[nodiscard]] float length() const;
        [[nodiscard]] sf::Vector2f center() const;
        [[nodiscard]] sf::Vector2f direction() const;
        [[nodiscard]] sf::Vector2f reflect(const FloatLine& mirror) const;
        static sf::Vector2f normalDirection(const FloatLine& line);
        static FloatLine normal(const FloatLine& line);
        static sf::Vector2f reflect(const sf::Vector2f& vec, const FloatLine& mirror);
    };
}



