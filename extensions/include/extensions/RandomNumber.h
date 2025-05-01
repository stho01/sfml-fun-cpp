//
// Created by stho on 12.04.2025.
//

#pragma once

#include <random>
#include <SFML/Graphics.hpp>
#include "Range.h"

namespace stho {

    class RandomNumber {
    public:

        static int next(const int min, const int max) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(
                std::min(min, max),
                std::max(min, max));

            return dis(gen);
        }

        static int next(const Rangei& range) {
            return next(range.min, range.max);
        }

        static float nextFloat(const float min, const float max) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution dis(
                std::min(min, max),
                std::max(min, max));
            return dis(gen);
        }

        static float nextFloat(const Rangef& range) {
            return nextFloat(range.min, range.max);
        }

        static sf::Vector2f vector2fAndReflect(const int xMin, const int xMax, const int yMin, const int yMax) {
            if (xMin <= 0 || xMax <= 0 || yMin <= 0 || yMax <= 0)
                throw "Arguments must be greater that zero";

            const auto x = next(xMin, xMax) * (next(0, 2) == 1 ? -1 : 1);
            const auto y = next(yMin, yMax) * (next(0, 2) == 1 ? -1 : 1);

            return sf::Vector2f(x, y);
        }

        static sf::Vector2f vector2fAndReflect(const int min, const int max) {
            return vector2fAndReflect(
                min,
                max,
                min,
                max);
        }

        static sf::Vector2f Vector2f(
            const float minX,
            const float maxX,
            const float minY,
            const float maxY) {

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> disX(minX, maxX);
            std::uniform_real_distribution<float> disY(minY, maxY);

            return sf::Vector2f(disX(gen), disY(gen));
        }

        static sf::Vector2f Vector2f(sf::FloatRect rect) {
            const auto xMin = rect.position.x;
            const auto xMax = rect.position.x + rect.size.x;
            const auto yMin = rect.position.y;
            const auto yMax = rect.position.y + rect.size.y;
            return Vector2f(xMin, xMax, yMin, yMax);
        }
    };

}