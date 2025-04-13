//
// Created by stho on 11.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Mathf.h"
#include "FloatCircle.h"

namespace stho {

    class FloatLine
    {
    public:
        sf::Vector2f p1;
        sf::Vector2f p2;

        FloatLine(float x1, float y1, float x2, float y2):
            p1(x1, y1),
            p2(x2, y2) {}

        FloatLine(sf::Vector2f p1, sf::Vector2f p2):
            p1(p1),
            p2(p2) {}

        FloatLine(FloatLine& line):
            p1(line.p1),
            p2(line.p2) {}

        bool intersects(const FloatLine& line, sf::Vector2f& intersection) const;
        bool intersects(const FloatCircle& circle, std::vector<sf::Vector2f>& intersections) const;

        float length() const {
            return (p2 - p1).length();
        }

        sf::Vector2f center() const {
            const auto delta = p2 - p1;
            const auto dir = delta.normalized();
            const auto halfLength = delta.length() * .5f;
            return p1 + dir * halfLength;
        }

        sf::Vector2f direction() {
            return (p2 - p1).normalized();
        }

        sf::Vector2f reflect(const FloatLine& mirror) {
            const auto n = normalDirection(mirror);
            const auto d = direction();
            return Mathf::reflect(d, n);
        }

        static sf::Vector2f normalDirection(const FloatLine& line) {
            return Mathf::normalDirection(line.p1, line.p2);
        }

        static FloatLine normal(const FloatLine& line) {
            const auto normal = Mathf::normal(line.p1, line.p2);

            return FloatLine(
                std::get<0>(normal),
                std::get<1>(normal));
        }

        static sf::Vector2f reflect(const sf::Vector2f& vec, FloatLine mirror)
        {
            const auto mirrorDirection = normalDirection(mirror);
            return Mathf::reflect(vec, mirrorDirection);
        }
    };
}



