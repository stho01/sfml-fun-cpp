//
// Created by stho on 10.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <extensions/extensions.h>
#include <vector>
#include "Cell.h"

class MinesweeperRenderer;

class Game final : public stho::GameBase {
public:

    explicit Game(
        sf::RenderWindow* window,
        const int width,
        const int height,
        const int mineCount);

    void initialize() override;
    void update() override;
    void render() override;
    void unload() override;

    void reset();

    [[nodiscard]] const std::vector<Cell>& getCells();
    [[nodiscard]] bool isGameOver() const;
    [[nodiscard]] const std::string& getGameStatus() const;
    [[nodiscard]] const sf::Vector2i& getCellSize() const;

private:
    std::vector<Cell> _cells{};
    int _boardWidth{20};
    int _boardHeight{20};
    int _mineCount{5};
    bool _initialized{false};
    sf::Vector2i _cellSize{10,10};
    bool _gameOver{false};
    std::string _gameStatus;
    MinesweeperRenderer* _renderer{nullptr};

    sf::Vector2i _calculateCellSize() const;
    void _handleMouseButtonPressed(sf::Mouse::Button button);
    void _scanAreaAround(const Cell& cell, std::function<void(Cell& cell)> callback);
    Cell* _getCell(const sf::Vector2i& pos);
    bool _revealCell(Cell& cell);
    void _enterGameOver(const std::string& status);
    bool _checkWinCondition() const;
};
