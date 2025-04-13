//
// Created by stho on 11.04.2025.
//

#pragma once

#include <cmath>

namespace stho {
    class PolarVector2f
    {
    public:
        PolarVector2f(const float r, const sf::Angle angle)
            : m_r(r) {
            setAngle(angle);
        }

        [[nodiscard]] float getR() const { return m_r; }

        float setR(const float& r) { return this->m_r = r; }

        [[nodiscard]] sf::Angle getAngle() const { return m_angle; }

        void setAngle(const sf::Angle& angle) {
            this->m_angle = angle.wrapUnsigned();
        }

    private:
        sf::Angle m_angle;
        float m_r;
    };
}