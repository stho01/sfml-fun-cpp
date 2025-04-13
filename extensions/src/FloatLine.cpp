//
// Created by stho on 11.04.2025.
//

#include "extensions/Mathf.h"
#include "extensions/FloatLine.h"

stho::FloatLine::FloatLine(const float x1, const float y1, const float x2, const float y2):
    p1(x1, y1),
    p2(x2, y2) {}

stho::FloatLine::FloatLine(const sf::Vector2f p1, const sf::Vector2f p2):
    p1(p1),
    p2(p2) {}

bool stho::FloatLine::intersects(const FloatLine& line, sf::Vector2f& intersection) const {
    const auto x1 = line.p1.x;
    const auto y1 = line.p1.y;
    const auto x2 = line.p2.x;
    const auto y2 = line.p2.y;

    const auto x3 = this->p1.x;
    const auto y3 = this->p1.y;
    const auto x4 = this->p2.x;
    const auto y4 = this->p2.y;

    const auto den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (den == 0)
        return false;

    const auto t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    const auto u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

    if (t > 0 && t < 1 && u > 0) {

        intersection = sf::Vector2f(
            x1 + t * (x2 - x1),
            y1 + t * (y2 - y1));

        return true;
    }

    return false;
}

bool stho::FloatLine::intersects(const FloatCircle& circle, std::vector<sf::Vector2f>& intersections) const {
    const auto circlePos = sf::Vector2f(circle.x, circle.y);
    const auto r = circle.radius;
    const auto point1 = this->p1 - circlePos; // translate p1 to circle local space
    const auto point2 = this->p2 - circlePos; // translate p2 to circle local space
    const auto d = point2 - point1;

    const auto a = d.lengthSquared();
    const auto b = 2 * (d.x * point1.x + d.y * point1.y);
    const auto c = point1.lengthSquared() - r * r;

    const auto delta = b * b - 4 * a * c;

    if (delta < 0)
        return false;

    if (delta == 1) {
        const auto u = -b / (2 * a);
        const auto intersection = this->p1 + u * d;
        intersections.push_back(intersection);
        return true;
    }

    const auto sqrDelta = -std::sqrt(delta);
    const auto u1 = (-b - sqrDelta) / (2 * a);
    const auto u2 = (-b + sqrDelta) / (2 * a);

    const auto intersection1 = this->p1 + u1 * d;
    const auto intersection2 = this->p1 + u2 * d;
    intersections.push_back(intersection1);
    intersections.push_back(intersection2);
    return true;
}

float stho::FloatLine::length() const {
    return (p2 - p1).length();
}

sf::Vector2f stho::FloatLine::center() const {
    const auto delta = p2 - p1;
    const auto dir = delta.normalized();
    const auto halfLength = delta.length() * .5f;
    return p1 + dir * halfLength;
}

sf::Vector2f stho::FloatLine::direction() const {
    return (p2 - p1).normalized();
}

sf::Vector2f stho::FloatLine::reflect(const FloatLine& mirror) const {
    const auto n = normalDirection(mirror);
    const auto d = direction();
    return Mathf::reflect(d, n);
}

sf::Vector2f stho::FloatLine::normalDirection(const FloatLine& line) {
    return Mathf::normalDirection(line.p1, line.p2);
}

stho::FloatLine stho::FloatLine::normal(const FloatLine& line) {
    const auto normal = Mathf::normal(line.p1, line.p2);

    return {
        std::get<0>(normal),
        std::get<1>(normal)};
}

sf::Vector2f stho::FloatLine::reflect(const sf::Vector2f& vec, const FloatLine& mirror) {
    const auto mirrorDirection = normalDirection(mirror);
    return Mathf::reflect(vec, mirrorDirection);
}