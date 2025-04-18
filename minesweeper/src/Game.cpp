//
// Created by stho on 10.04.2025.
//

#include <iostream>
#include "Game.h"
#include "MinesweeperRenderer.h"

Game::Game(
    sf::RenderWindow* window,
    const int width,
    const int height,
    const int mineCount)
    : GameBase(window)
    , _boardWidth(width)
    , _boardHeight(height)
    , _mineCount(mineCount)
    , _gameStatus("Game in progress")
{
    _cellSize = _calculateCellSize();
}

void Game::initialize() {
    Logger::Info("Initialized sprites");
    _initialized = true;
    _renderer = new MinesweeperRenderer(this, m_window);

    m_window->setTitle("Minesweeper");
    m_window->setFramerateLimit(10);

    setMouseButtonPressedHandler([this](const sf::Mouse::Button button) {
        _handleMouseButtonPressed(button);
    });

    setWindowResizeHandler([this](const sf::Vector2u size) {
        if (size.x % _boardWidth != 0 || size.y % _boardHeight != 0) {
            auto newX = size.x - (size.x % _boardWidth);
            const auto newCellSize = static_cast<float>(newX) / static_cast<float>(_boardWidth);
            auto newY = static_cast<unsigned int>(newCellSize * static_cast<float>(_boardHeight));
            m_window->setSize({newX, newY});
            m_window->setView(sf::View {
                windowCenter(),
                {static_cast<float>(newX), static_cast<float>(newY)}
            });
        }

        _cellSize = _calculateCellSize();
        auto winSize = m_window->getSize();
        Logger::Info("window size: x {}, y {}", winSize.x, winSize.y);
        Logger::Info("cell size: x {}, y {}", _cellSize.x, _cellSize.y);
    });

    reset();
}

void Game::update() { }

void Game::render() {
    _renderer->render();
}

void Game::unload() {
    std::cout << "Game unloaded!" << std::endl;
}

void Game::reset() {
    if (!_initialized) {
        throw std::runtime_error("Game not initialized");
    }

    _gameOver = false;

    // init board
    _cells.clear();
    const int size = _boardWidth * _boardHeight;
    for (int i = 0; i < size; i++) {
        const int x = i % _boardWidth;
        const int y = i / _boardWidth;
        _cells.emplace_back(x, y);
    }

    // place mines
    if (_boardWidth * _boardHeight < _mineCount) {
        throw std::runtime_error("Too many mines for the board size");
    }

    int placedMines = 0;
    while (placedMines < _mineCount) {
        Cell* cell = nullptr;

        do {
            const int randomIndex = stho::RandomNumber::next(0, size - 1);
            cell = &_cells[randomIndex];
        } while (cell->isMine());

        cell->setMine(true);
        placedMines++;
    }

    // update mine memory
    for (Cell& cell : _cells) {
        _scanAreaAround(cell, [this, &cell](const Cell& neighbor) {
            if (neighbor.isMine()) {
                cell.addOneToNeighborMines();
            }
        });
    }
}

const std::vector<Cell>& Game::getCells() { return _cells; }
bool Game::isGameOver() const { return _gameOver; }
const std::string& Game::getGameStatus() const { return _gameStatus; }
const sf::Vector2i& Game::getCellSize() const { return _cellSize; }

sf::Vector2i Game::_calculateCellSize() const {
    const auto windowSize = m_window->getSize();
    const float x = static_cast<float>(windowSize.x) / static_cast<float>(_boardWidth);
    const float y = static_cast<float>(windowSize.y) / static_cast<float>(_boardHeight);

    return {
       static_cast<int>(x),
       static_cast<int>(y)
    };
}

void Game::_handleMouseButtonPressed(sf::Mouse::Button button) {

    if (button != sf::Mouse::Button::Left)
        return;

    const auto pos = getMousePosition();

    if (!_gameOver && windowBounds().contains(static_cast<sf::Vector2f>(pos)))
    {
        const auto cellSize = _cellSize;
        const sf::Vector2i cellPos = {
            pos.x /  cellSize.x,
            pos.y /  cellSize.y
        };

        Cell* cell = _getCell(cellPos);
        const auto mineHit = this->_revealCell(*cell);

        if (mineHit) {
            _enterGameOver("Game over");
        } else if (_checkWinCondition()) {
            _enterGameOver("Congrats comrade!");
        }
    }
}

void Game::_scanAreaAround(const Cell& cell, std::function<void(Cell& cell)> callback) {
    const auto x = cell.x();
    const auto y = cell.y();

    for (auto xOff = -1; xOff <= 1; xOff++)
    for (auto yOff = -1; yOff <= 1; yOff++)
    {
        const auto xToCheck = x + xOff;
        const auto yToCheck = y + yOff;

        if (xToCheck >= 0
            && yToCheck >= 0
            && xToCheck < _boardWidth
            && yToCheck < _boardHeight)
        {
            Cell* other = _getCell({xToCheck, yToCheck});
            if (other != &cell) {
                callback(*other);
            }
        }
    }
}

Cell* Game::_getCell(const sf::Vector2i& pos) {
    const int index = pos.y * _boardWidth + pos.x;
    return &_cells[index];
}

bool Game::_revealCell(Cell& cell) {
    if (cell.isRevealed())
        return cell.isMine();

    cell.setRevealed();
    if (cell.getNeighborMines() == 0) {
        _scanAreaAround(cell, [this](Cell& neighbor) {
            if (!neighbor.isRevealed()) {
                _revealCell(neighbor);
            }
        });
    }

    return cell.isMine();
}

void Game::_enterGameOver(const std::string& status) {
    _gameOver = true;
    _gameStatus = status;
    for (Cell& cell : _cells) {
        cell.setRevealed();
    }
}

bool Game::_checkWinCondition() const {
    bool win = true;

    for (const Cell& cell : _cells) {
        if (cell.isMine()) {
            continue;
        }
        if (!cell.isRevealed()) {
            win = false;
            break;
        }
    }

    return win;
}