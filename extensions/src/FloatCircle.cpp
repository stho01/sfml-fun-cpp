//
// Created by stho on 11.04.2025.
//

#include "extensions/FloatCircle.h"
#include <cmath>

bool stho::FloatCircle::intersects(const FloatCircle& circle) const
{
    float c1;
    return this->intersects(circle, c1);
}

bool stho::FloatCircle::intersects(const FloatCircle& circle, float& overlap) const {
    const auto dx = circle.x - this->x;
    const auto dy = circle.x - this->y;
    const auto mSquared = dx * dx + dy * dy;
    const auto r = this->radius + circle.radius;
    const auto rSquared = r * r;

    overlap = r - std::sqrt(mSquared);

    return mSquared <= rSquared;
}

bool stho::FloatCircle::contains(const float& x, const float& y) const {
    return this->intersects(FloatCircle(x, y));
}