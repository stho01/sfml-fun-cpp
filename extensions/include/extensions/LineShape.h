//
// Created by stenm on 16.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>

namespace stho {

class LineShape : public sf::Shape {
public:
    sf::Vector2f p1{0,0};
    sf::Vector2f p2{0,0};

    explicit LineShape(float x1, float y1, float x2, float y2);
    explicit LineShape(sf::Vector2f p1, sf::Vector2f p2);
    std::size_t getPointCount() const override;
    sf::Vector2f getPoint(std::size_t index) const override;

};

}