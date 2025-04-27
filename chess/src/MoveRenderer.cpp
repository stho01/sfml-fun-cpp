//
// Created by stenm on 27.04.2025.
//

#include "MoveRenderer.h"
#include "Board.h"
#include "Game.h"

MoveRenderer::MoveRenderer(sf::RenderTarget& renderTarget, Game& game)
  : _renderTarget(renderTarget), _game(game)
{
  _selectedCell.setFillColor(sf::Color(0x00000000));
  _selectedCell.setOutlineColor(sf::Color(0xC2653CFF));
  _selectedCell.setOutlineThickness(4.f);
  _possibleMove.setFillColor(sf::Color(0x00FF0088));
}

MoveRenderer::~MoveRenderer() {
  Logger::Info("MoveRenderer destroyed");
}

void MoveRenderer::render(const MoveController& moveController) {
  const auto& board = _game.getBoard();

  if (moveController.hasSelectedCell()) {
    const auto screenPosition = board.positionToScreenCoords(moveController.getSelectedCell()->getPosition());
    constexpr int padding = 2.f;

    _selectedCell.setPosition({
      screenPosition.x + (_selectedCell.getOutlineThickness() + padding) / 2.f,
      screenPosition.y + (_selectedCell.getOutlineThickness() + padding) / 2.f
    });

    _selectedCell.setSize({
      board.cellSize().x - (_selectedCell.getOutlineThickness() + padding),
      board.cellSize().y - (_selectedCell.getOutlineThickness() + padding)
    });

    _renderTarget.draw(_selectedCell);

    for (const auto& cell : moveController.getLegalMoves()) {
      _possibleMove.setPosition(static_cast<sf::Vector2f>(board.positionToScreenCoords(cell->getPosition())));
      _possibleMove.setSize(board.cellSize());
      _renderTarget.draw(_possibleMove);
    }
  }
}
