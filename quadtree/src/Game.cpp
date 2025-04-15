//
// Created by stho on 10.04.2025.
//

#include <iostream>
#include <extensions/extensions.h>
#include "Game.h"

void Game::initialize() {

    Logger::SetMinimumLogLevel(LOG_DEBUG);
    constexpr auto radius = 5.0f;

    m_quadTree = std::make_unique<stho::QuadTree<stho::FloatCircle*>>(windowBounds(), 4);

    for (int i = 0; i < numberOfCircles; i++) {
        const auto pos = stho::RandomNumber::Vector2f(windowBounds());
        auto circle = new stho::FloatCircle(pos, radius);
        m_circles.push_back(circle);
        m_quadTree->insert(pos, circle);
    }

    m_circle.setOrigin({radius, radius});
    m_circle.setFillColor(sf::Color(0xFFFFFF55));
    m_circle.setRadius(radius);
}

void Game::update() {
    const auto mousePosition = sf::Mouse::getPosition(*m_window);
    if (isButtonPressed(sf::Mouse::Button::Left)) {
        if (!m_start.has_value()) {
            m_start = sf::Vector2f(mousePosition);
        }

        const auto end = sf::Vector2f(mousePosition);

        m_rectSelection = sf::FloatRect(
            {std::min(m_start->x, end.x), std::min(m_start->y, end.y)},
            {std::abs(m_start->x - end.x), std::abs(m_start->y - end.y)});


        const auto radius = std::abs(m_start->x - end.x);
        m_circleSelection = stho::FloatCircle(m_start.value(), radius);

    } else {
        m_start.reset();
        m_rectSelection.reset();
    }
}

void Game::render() {
    const auto boundaries = m_quadTree->getBoundaries();
    for (const auto boundary : boundaries) {
        sf::RectangleShape shape;
        shape.setPosition(boundary.position);
        shape.setSize(boundary.size);
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color(0xFFFF0011));
        shape.setOutlineThickness(1.0f);
        this->m_window->draw(shape);
    }

    std::list<stho::FloatCircle*> selected;

    if (!m_circularSelectionEnabled && m_rectSelection.has_value()) {
        selected = m_quadTree->queryRange(m_rectSelection.value());
    }
    else if (m_circularSelectionEnabled && m_circleSelection.has_value()) {
        selected = m_quadTree->queryRange(m_circleSelection.value());
    }

    for (const auto circle : m_circles) {
        auto color = sf::Color(0xFFFFFF55);
        if (std::ranges::find(selected, circle) != selected.end()) {
            color = sf::Color::Cyan;
        }

        m_circle.setPosition({circle->x, circle->y});
        m_circle.setFillColor(color);
        m_window->draw(m_circle);
    }

    if (!m_circularSelectionEnabled && m_rectSelection.has_value()) {
        const auto selection = m_rectSelection.value();
        sf::RectangleShape rect;
        rect.setSize(selection.size);
        rect.setPosition(selection.position);
        rect.setFillColor(sf::Color(0x00FF0022));
        rect.setOutlineColor(sf::Color::Green);
        rect.setOutlineThickness(1.0f);
        m_window->draw(rect);
    }

    if (m_circularSelectionEnabled && m_circleSelection.has_value()) {
        auto selection = m_circleSelection.value();
        sf::CircleShape circle;
        circle.setRadius(selection.radius);
        //circle.setOrigin({selection.radius, selection.radius});
        circle.setPosition({selection.x - selection.radius, selection.y - selection.radius});
        circle.setFillColor(sf::Color(0x00FF0022));
        circle.setOutlineColor(sf::Color::Green);
        circle.setOutlineThickness(1.0f);
        m_window->draw(circle);

        const sf::FloatRect rect2({
          selection.x - selection.radius,
          selection.y - selection.radius
      }, {
          selection.radius * 2,
          selection.radius * 2
      });

        sf::RectangleShape rect;
        rect.setSize(rect2.size);
        rect.setPosition(rect2.position);
        rect.setFillColor(sf::Color(0xFF000022));
        rect.setOutlineColor(sf::Color::Red);
        rect.setOutlineThickness(1.0f);
        m_window->draw(rect);
    }
}

void Game::unload() {
    std::cout << "Game unloaded!" << std::endl;
}

void Game::toggleSelectionType() {
    m_circularSelectionEnabled = !m_circularSelectionEnabled;
}