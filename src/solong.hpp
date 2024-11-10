#ifndef SOLONG_HPP
# define SOLONG_HPP

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <SFML/System.hpp>
# include <SFML/Graphics/RectangleShape.hpp>
# include "SFML/Graphics/RenderWindow.hpp"
# include <iostream>
# include <fstream>
# include <vector>

# define tileSize 32

class Game {
    private:
        int _totalItems;
        int _collectedItems;

        int _currentLevel;
        int _maxLevel;

        sf::Text _messageText;
        sf::Clock _clock;
        bool _showMessage = false;
        bool _goalReached = false;
        sf::Font _font;

        sf::Vector2i _enemyPos;
        sf::Clock _enemyMoveClock;
        bool _gameOver = false;

        sf::RectangleShape _redFilter;
    
    public:
        Game(int totalItem, const sf::Vector2i enemyStartPos) : _totalItems(totalItem), _collectedItems(0), _enemyPos(enemyStartPos) , _currentLevel(1), _maxLevel(3) {

            if (!_font.loadFromFile("src/Roboto-Medium.ttf")) {
                std::cerr << "Failed to load font.\n";
            }
            _messageText.setFont(_font);

            _messageText.setCharacterSize(24);
            _messageText.setFillColor(sf::Color::White);
            _messageText.setPosition(10, 10);

            _redFilter.setSize(sf::Vector2f(800, 600));
            _redFilter.setFillColor(sf::Color(255, 0, 0, 100));         
        };

        int getTotalItem() const { return this->_totalItems; };
        int getCollectedItem() const { return this->_collectedItems; };
        int getCurrentLevel() const { return this->_currentLevel; };
        sf::Vector2i getEnemyPos() const { return this->_enemyPos; };
        bool getGoalReached() const { return this->_goalReached; };
        int getMaxLevel() const { return _maxLevel; };

        bool canReachGoal() {
            return _collectedItems == _totalItems;
        }

        void collectItem() {
            if (_collectedItems < _totalItems) {
                _collectedItems++;
            displayItemMessage("Item collected!");
            }
        }

        void displayItemMessage(const std::string& messgae) {
            if (!_goalReached) {
                _messageText.setString(messgae);
                _showMessage = true;
                _clock.restart();
            }
        }

        void displayGoalMessage() {
            _goalReached = true;
            _messageText.setString("Level Cleared! Press Enter to Continue");
        }

        void update(sf::RenderWindow& window) {
            if (_goalReached) {
                window.draw(_messageText);
            }
            if (_showMessage) {
                window.draw(_messageText);
                if (_clock.getElapsedTime().asSeconds() > 0.5f) {
                    _showMessage = false;
                }
            }
            if (_gameOver) {
                window.draw(_redFilter);
                _messageText.setString("Game Over");
                window.draw(_messageText);
            }
        }

        void nextLevel(const sf::Vector2i& newEnemyPos) {
            if (_currentLevel < _maxLevel) {
                _currentLevel++;
                _goalReached = false;
                _collectedItems = 0;
                _enemyPos = newEnemyPos;
            }
        }

        void moveEnemy(std::vector<std::vector<char>>& map) {
            if (_enemyMoveClock.getElapsedTime().asSeconds() > 0.5f) {
                _enemyMoveClock.restart();

                int direction = std::rand() % 4;
                sf::Vector2i newEnemyPos = _enemyPos;

                switch(direction) {
                    case 0: newEnemyPos.y -= 1; break;
                    case 1: newEnemyPos.y += 1; break;
                    case 2: newEnemyPos.x -= 1; break;
                    case 3: newEnemyPos.x += 1; break;
                }

                if (newEnemyPos.y >= 0 && newEnemyPos.y < map.size() &&
                    newEnemyPos.x >= 0 && newEnemyPos.x < map[0].size() &&
                    map[newEnemyPos.y][newEnemyPos.x] != '1') {
                        _enemyPos = newEnemyPos;
                }
            }
        }

        bool checkGameOver(const sf::Vector2i& playerPos) {
            if (playerPos == _enemyPos) {
                _gameOver = true;
                return true;
            }
            return false;
        }

        void resetEnemyPosition(const sf::Vector2i& newEnemyPos) {
            _enemyPos = newEnemyPos;
        }
};

sf::Sprite put_texture(sf::Texture& texture, std::string path);
std::vector<std::vector<char>> read_map(const std::string& filename, sf::Vector2i& playerPos, sf::Vector2i& enemyStartPos, int& totalItems);
void movement(sf::Vector2i &playerPos, std::vector<std::vector<char>>& map, sf::Event event, Game& game);

#endif