//
// Created by stenm on 21.04.2025.
//

#include "PieceRenderer.h"
#include <extensions/Mathf.h>

PieceRenderer::PieceRenderer(sf::RenderTarget& renderTarget, SpriteAtlas& spriteAtlas)
    : _renderTarget(renderTarget), _spriteAtlas(spriteAtlas) { }

PieceRenderer::~PieceRenderer() {
    Logger::Info("PieceRenderer destroyed");
}

void PieceRenderer::initialize() {
    const std::array<std::pair<PieceColor, std::string>, 2> colors = {
        std::make_pair(White, "white"),
        std::make_pair(Black, "black")
    };
    const std::array<std::pair<PieceType, std::string>, 6> pieces = {
        std::make_pair(Pawn, "pawn"),
        std::make_pair(Bishop, "bishop"),
        std::make_pair(Knight, "knight"),
        std::make_pair(Rook, "rook"),
        std::make_pair(Queen, "queen"),
        std::make_pair(King, "king")
    };

    for (auto i = 0; i < pieces.size(); i++) {
        for (auto j = 0; j < colors.size(); j++) {
            _names[{pieces[i].first, colors[j].first}] = pieces[i].second + "-" + colors[j].second;
        }
    }
}

void PieceRenderer::render(const Board& board, const Piece& piece) const {
    if (const auto& sprite = _getPieceSprite(piece); sprite)
    {
        const auto pos =
            stho::Vector2f::multiply(board.cellSize(), piece.position)
            + (board.cellSize() / 2.f)
            + board.getPosition()
            - stho::Vector2f::multiply(_scale, _getSpriteCenter(*sprite));

        sprite->setPosition(pos);

        const sf::Sprite& spriteRef = *sprite;
        _renderTarget.draw(spriteRef);
    }
}

sf::Vector2f PieceRenderer::_getSpriteCenter(const sf::Sprite& sprite) {
    const auto textureSize = sprite.getTextureRect().size;
    return {
        textureSize.x / 2.f,
        textureSize.y / 2.f
    };
}

const std::unique_ptr<sf::Sprite>& PieceRenderer::_getPieceSprite(const Piece& piece) const {
    const auto name = _names.find({piece.pieceType, piece.color});
    if (name == _names.end()) {
        return nullptr;
    }
    const auto& sprite = _spriteAtlas.getSprite(name->second);
    if (sprite) {
        sprite->setScale(_scale);
    }
    return sprite;
}
