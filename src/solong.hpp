#ifndef SOLONG_HPP
# define SOLONG_HPP

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <SFML/System.hpp>
# include "SFML/Graphics/RenderWindow.hpp"
# include <iostream>
# include <fstream>
# include <vector>

# define tileSize 32

class Game {
    private:
        int _totalItems;
        int _collectedItems;
        sf::Text _messageText;
        sf::Clock _clock;
        bool _showMessage = false;
        bool _goalReached = false;
        sf::Font _font;
    
    public:
        Game(int totalItem) : _totalItems(totalItem), _collectedItems(0) {

            if (!_font.loadFromFile("src/Roboto-Medium.ttf")) {
                std::cerr << "Failed to load font.\n";
            }
            _messageText.setFont(_font);

            _messageText.setCharacterSize(24);
            _messageText.setFillColor(sf::Color::White);
            _messageText.setPosition(10, 10);            
        };

        int getTotalItem() const { return this->_totalItems; };
        int getCollectedItem() const { return this->_collectedItems; };

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
            _messageText.setString("Goal");
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
        }
};

sf::Sprite put_texture(sf::Texture& texture, std::string path);
std::vector<std::vector<char>> read_map(const std::string& filename, sf::Vector2i& playerPos, int& totalItems);
void movement(sf::Vector2i &playerPos, std::vector<std::vector<char>>& map, sf::Event event, Game& game);

#endif