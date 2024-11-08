#ifndef SOLONG_HPP
# define SOLONG_HPP

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include "SFML/Graphics/RenderWindow.hpp"
# include <iostream>
# include <fstream>
# include <vector>

# define tileSize 32

sf::Sprite put_texture(sf::Texture& texture, std::string path);
std::vector<std::vector<char>> read_map(const std::string& filename, sf::Vector2i& playerPos);
void movement(sf::Vector2i &playerPos, const std::vector<std::vector<char>>& map, sf::Event event);
#endif