//
// Created by stho on 10.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <extensions/extensions.h>

class Game final : public stho::GameBase {
public:
    explicit Game(std::shared_ptr<sf::RenderWindow> window) : GameBase(window){
        setClearColor(sf::Color::Black);
    }

    void initialize() override;
    void update() override;
    void render() override;
    void unload() override;

private:
    std::shared_ptr<sf::Texture> m_texture{nullptr};
    std::shared_ptr<sf::Sprite> m_sprite1{nullptr};
    std::shared_ptr<sf::Sprite> m_sprite2{nullptr};
};
