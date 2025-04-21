//
// Created by stho on 11.04.2025.
//

#pragma once

#include <SFML/System.hpp>
#include "PolarVector2f.h"

namespace stho {

    class Vector2f {
    public:
        constexpr static sf::Vector2f ZERO {0,0};
        constexpr static sf::Vector2f RIGHT {1,0};
        constexpr static sf::Vector2f LEFT  {-1,0};
        constexpr static sf::Vector2f UP {1,-1};
        constexpr static sf::Vector2f DOWN {1,1};

        static sf::Vector2f multiply(const sf::Vector2f& lhs, const sf::Vector2f& rhs);
        static sf::Vector2f multiply(const sf::Vector2i& lhs, const sf::Vector2f& rhs);
        static sf::Vector2f multiply(const sf::Vector2f& lhs, const sf::Vector2i& rhs);

        static sf::Vector2f divide(const sf::Vector2f& lhs, const sf::Vector2f& rhs);
        static sf::Vector2f divide(const sf::Vector2i& lhs, const sf::Vector2f& rhs);
        static sf::Vector2f divide(const sf::Vector2f& lhs, const sf::Vector2i& rhs);
    };

    class Mathf {
    public:
        static PolarVector2f ToPolarCoordinates(const sf::Vector2f& vector);
        static int quadrant(const sf::Vector2f& vector);
        static sf::Vector2f lookAt(const sf::Vector2f& pos, const sf::Vector2f& point);
        static std::tuple<sf::Vector2f, sf::Vector2f> normal(const sf::Vector2f& p1, const sf::Vector2f& p2);
        static sf::Vector2f normalDirection(const sf::Vector2f& p1, const sf::Vector2f& p2);
        static sf::Vector2f reflect(const sf::Vector2f& vec, const  sf::Vector2f& normal);
    };

}