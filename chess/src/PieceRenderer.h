//
// Created by stenm on 21.04.2025.
//

#pragma once

#include <unordered_map>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Board.h"
#include "SpriteAtlas.h"

class PieceRenderer {
public:
    PieceRenderer(sf::RenderTarget& renderTarget, SpriteAtlas& spriteAtlas);
    ~PieceRenderer();
    void initialize();
    void render(const Board& board, const Piece& piece) const;
    void setScale(const sf::Vector2f& scale) { _scale = scale; }
    sf::Vector2f getScale() const { return _scale; }

private:
    sf::RenderTarget& _renderTarget;
    SpriteAtlas& _spriteAtlas;
    std::unordered_map<std::pair<PieceType, PieceColor>, std::string> _names;
    sf::Vector2f _scale{1.f,1.f};

    static sf::Vector2f _getSpriteCenter(const sf::Sprite& sprite);
    sf::Sprite* _getPieceSprite(const Piece& piece) const;
};
