//
// Created by stho on 11.04.2025.
//

#include "extensions/Mathf.h"
#include <format>
#include <numbers>
#include <string>

namespace stho {

    sf::Vector2f Vector2f::multiply(const sf::Vector2f& lhs, const sf::Vector2f& rhs) {
        return { lhs.x * rhs.x, lhs.y * rhs.y };
    }
    sf::Vector2f Vector2f::multiply(const sf::Vector2i& lhs, const sf::Vector2f& rhs) {
        return { lhs.x * rhs.x, lhs.y * rhs.y };
    }
    sf::Vector2f Vector2f::multiply(const sf::Vector2f& lhs, const sf::Vector2i& rhs) {
        return { lhs.x * rhs.x, lhs.y * rhs.y };
    }
    sf::Vector2f Vector2f::divide(const sf::Vector2f& lhs, const sf::Vector2f& rhs) {
        return { lhs.x / rhs.x, lhs.y / rhs.y };
    }
    sf::Vector2f Vector2f::divide(const sf::Vector2i& lhs, const sf::Vector2f& rhs) {
        return { lhs.x / rhs.x, lhs.y / rhs.y };
    }
    sf::Vector2f Vector2f::divide(const sf::Vector2f& lhs, const sf::Vector2i& rhs) {
        return { lhs.x / rhs.x, lhs.y / rhs.y };
    }

    std::string Vector2f::asString(sf::Vector2f vector2) {
        return std::format("x: {}, y: {}", vector2.x, vector2.y);
    }

    PolarVector2f Mathf::ToPolarCoordinates(const sf::Vector2f& vector) {
        if (vector == Vector2f::ZERO)
            return PolarVector2f(0, sf::degrees(0));

        const int quadrant = Mathf::quadrant(vector);

        int quadrantAddition = 0;
        switch (quadrant)
        {
            case 2:
                quadrantAddition = 180;
            break;
            case 3:
                quadrantAddition = 180;
            break;
            case 4:
                quadrantAddition = 360;
            break;
            default:
                quadrantAddition = 0;
            break;
        }

        const float degrees = (float)(std::atan(vector.y / vector.x) * (180 / std::numbers::pi));
        const PolarVector2f polar(
            vector.length(),
            sf::degrees(degrees + quadrantAddition + 90)
        );

        return polar;
    }

    int Mathf::quadrant(const sf::Vector2f& vector) {
        return vector.x >= 0 && vector.y >= 0 ? 1
            : vector.x < 0 && vector.y >= 0 ? 2
            : vector.x < 0 && vector.y < 0 ? 3
            : vector.x >= 0 && vector.y < 0 ? 4
            : 0;
    }

    sf::Vector2f Mathf::lookAt(const sf::Vector2f& pos, const sf::Vector2f& point) {
        return (point - pos).normalized();
    }

    std::tuple<sf::Vector2f, sf::Vector2f> Mathf::normal(const sf::Vector2f& p1, const sf::Vector2f& p2) {
        const sf::Vector2f d = p2 - p1;
        const sf::Vector2f n1(-d.y, d.x);
        const sf::Vector2f n2(d.y, -d.x);
        return std::make_tuple(n1, n2);
    }

    sf::Vector2f Mathf::normalDirection(const sf::Vector2f& p1, const sf::Vector2f& p2)
    {
        const auto n = normal(p1, p2);
        return (std::get<0>(n) - std::get<1>(n)).normalized();
    }

    sf::Vector2f Mathf::reflect(const sf::Vector2f& vec, const  sf::Vector2f& normal) {
        const auto d = vec.normalized();
        return d - 2 * d.dot(normal) * normal;
    }

    double Mathf::degreeToRadian(const double& degree) {
        return degree * (std::numbers::pi / 180.f);
    }

    double Mathf::radianToDegree(const double& radian) {
        return radian * (180.f / std::numbers::pi);
    }

    sf::Vector2f Mathf::getDirectionFromDegrees(const double& degrees) {
        return getDirectionFromRadian(degreeToRadian(degrees));
    }

    sf::Vector2f Mathf::getDirectionFromRadian(const double& radian) {
        return sf::Vector2f(
            static_cast<float>(cos(radian)),
            static_cast<float>(sin(radian))
        );
    }
}
