//
// Created by stho on 11.04.2025.
//

#include "extensions/FloatLine.h"

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