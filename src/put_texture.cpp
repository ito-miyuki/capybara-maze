#include <SFML/Graphics.hpp>
#include <iostream>

sf::Sprite put_texture(sf::Texture& texture, std::string path) {
    if (!texture.loadFromFile(path)) {
        std::cerr << "Error loading texture" << std::endl;
        exit(1);
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    return sprite;
}