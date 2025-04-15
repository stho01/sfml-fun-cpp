//
// Created by stho on 10.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <extensions/extensions.h>
#include <iostream>

class Game final : public stho::GameBase {
public:
    int numberOfCircles{400};

    explicit Game(sf::RenderWindow* window) : GameBase(window){
        setClearColor(sf::Color::Black);
    }

    void initialize() override;
    void update() override;
    void render() override;
    void unload() override;

    void toggleSelectionType();

private:
    std::unique_ptr<stho::QuadTree<stho::FloatCircle*>> m_quadTree{nullptr};
    std::vector<stho::FloatCircle*> m_circles;
    sf::CircleShape m_circle;
    std::optional<sf::Vector2f> m_start;
    std::optional<sf::FloatRect> m_rectSelection;
    std::optional<stho::FloatCircle> m_circleSelection;
    bool m_circularSelectionEnabled{false};
};
