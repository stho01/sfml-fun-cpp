//
// Created by stenm on 16.04.2025.
//

#include "extensions/LineShape.h"

namespace stho {

    LineShape::LineShape(float x1, float y1, float x2, float y2)
        : p1(x1, y1), p2(x2, y2)
    {
        this->setFillColor(sf::Color::White);
    };

    LineShape::LineShape(sf::Vector2f p1, sf::Vector2f p2)
        : p1(p1), p2(p2)
    {
        this->setFillColor(sf::Color::White);
    };

    std::size_t LineShape::getPointCount() const {
        return 2;
    }

    sf::Vector2f LineShape::getPoint(std::size_t index) const {
        if (index == 0) {
            return p1;
        } else if (index == 1) {
            return p2;
        }
        return sf::Vector2f(0, 0);
    }
}
