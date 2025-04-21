//
// Created by stho on 10.04.2025.
//

#include <iostream>
#include "Game.h"

Game::Game(sf::RenderWindow* window) : GameBase(window){
    std::cout << "Mottatt: " << (window ? "ikke null" : "null") << "\n";
    setClearColor(sf::Color::Black);
}

void Game::initialize() {
    m_texture = std::make_shared<sf::Texture>("assets/texture.png");

    m_sprite1 = std::make_shared<sf::Sprite>(*m_texture);
    m_sprite1->setPosition(sf::Vector2f(100, 100));
    m_sprite2 = std::make_shared<sf::Sprite>(*m_texture);
    m_sprite2->setPosition(sf::Vector2f(200, 200));

    Logger::Info("Initialized sprites");
}

void Game::update() {
    // Logger::Info(std::format("Delta Time: {:.13f} seconds", static_cast<float>(stho::Timer::getDeltaTimeSeconds())));
}

void Game::render() {
    // Render game objects here
    getWindow()->draw(*m_sprite1);
    getWindow()->draw(*m_sprite2);


    auto radius = 50.0f;
    auto pos1 = sf::Vector2f({600, 300});
    stho::FloatCircle c1 { pos1.x, pos1.y, radius };

    auto pos2 = sf::Vector2f(sf::Mouse::getPosition(*getWindow()));
    stho::FloatCircle c2 { pos2.x, pos2.y, radius };

    auto distance = (pos2 - pos1).length();
    auto isColliding = distance < radius + radius;

    sf::Color color = isColliding ? sf::Color::Red : sf::Color::Green;

    sf::CircleShape circle;

    circle.setRadius(c1.radius);
    circle.setPosition({c1.x - c1.radius, c1.y - c1.radius});
    circle.setFillColor(color);
    getWindow()->draw(circle);

    circle.setRadius(c2.radius);
    circle.setPosition({c2.x - c2.radius, c2.y - c2.radius});
    circle.setFillColor(color);
    getWindow()->draw(circle);
}

void Game::unload() {
    std::cout << "Game unloaded!" << std::endl;
}