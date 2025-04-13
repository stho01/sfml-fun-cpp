//
// Created by stho on 10.04.2025.
//

#include <iostream>
#include "Game.h"

void Game::initialize() {
    m_texture = std::make_shared<sf::Texture>("assets/texture.png");

    m_sprite1 = std::make_shared<sf::Sprite>(*m_texture);
    m_sprite1->setPosition(sf::Vector2f(100, 100));
    m_sprite2 = std::make_shared<sf::Sprite>(*m_texture);
    m_sprite2->setPosition(sf::Vector2f(200, 200));

    Logger::Info("Initialized sprites");
}

void Game::update() {
    Logger::Info(std::format("Delta Time: {:.2f} seconds", static_cast<float>(stho::Timer::getDeltaTimeSeconds())));
}

void Game::render() {
    // Render game objects here
    getWindow()->draw(*m_sprite1);
    getWindow()->draw(*m_sprite2);
}

void Game::unload() {
    std::cout << "Game unloaded!" << std::endl;
}