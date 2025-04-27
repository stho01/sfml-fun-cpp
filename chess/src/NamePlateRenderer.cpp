//
// Created by stenm on 27.04.2025.
//

#include "NamePlateRenderer.h"
#include <extensions/extensions.h>
#include "Game.h"

const std::string NamePlateRenderer::WHITE = "WHITE";;
const std::string NamePlateRenderer::BLACK = "BLACK";;

NamePlateRenderer::NamePlateRenderer(sf::RenderTarget& renderTarget, Game& game)
  : _game(game), _renderTarget(renderTarget), _currentPlayerName(stho::Fonts::Roboto())
{ }

NamePlateRenderer::~NamePlateRenderer() {
  Logger::Info("NamePlateRenderer destroyed");
}

void NamePlateRenderer::render() {
  const auto& currentPlayer = _game.getCurrentPlayer();

  _currentPlayerName.setString(currentPlayer == White ? WHITE : BLACK);
  _currentPlayerName.setFillColor(currentPlayer == White ? sf::Color::Black : sf::Color::White);

  const auto textBounds = _currentPlayerName.getGlobalBounds();

  const auto windowCenter = _game.windowCenter();
  _currentPlayerName.setPosition({
      windowCenter.x - textBounds.size.x / 2.f,
      0.f
  });

  _rectangle.setSize({
    static_cast<float>(_game.windowWidth()),
    textBounds.size.y + 20.f
  });
  _rectangle.setPosition({
    0.f,
    textBounds.size.y / 2.f - 10.f
  });
  _rectangle.setFillColor(currentPlayer == White ? sf::Color::White : sf::Color::Black);

  _renderTarget.draw(_rectangle);
  _renderTarget.draw(_currentPlayerName);
}