#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/RenderWindow.hpp"

std::vector<std::vector<char>> read_map(const std::string& filename);

int main()
{
    std::vector<std::vector<char>> map = read_map("map/map2.txt");
    const int tileSize = 32;
    int rows = map.size(); // マップの行数
    int cols = map[0].size(); // マップの列数

    sf::RenderWindow window(sf::VideoMode(cols * tileSize, rows * tileSize), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        // ウィンドウで発生したイベント（キーボード、マウス、ウィンドウの閉じるボタンなど）を処理
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Blue);

        for (int row = 0; row < map.size(); ++row) {
            for (int col = 0; col < map[row].size(); col++) {
                if (map[row][col] == '1') {
                    sf::RectangleShape wall(sf::Vector2f(tileSize, tileSize));
                    wall.setFillColor(sf::Color::Blue);
                    wall.setPosition(col * tileSize, row * tileSize);
                    window.draw(wall);
                }
                else if (map[row][col] == '0') {
                    sf::RectangleShape path(sf::Vector2f(tileSize, tileSize));
                    path.setFillColor(sf::Color::White);
                    path.setPosition(col * tileSize, row * tileSize);
                    window.draw(path);
                }
                else if (map[row][col] == 'C') {
                    sf::RectangleShape item(sf::Vector2f(tileSize, tileSize));
                    item.setFillColor(sf::Color::Red);
                    item.setPosition(col * tileSize, row * tileSize);
                    window.draw(item);
                }
            }
        }
        window.display();
    }

    return 0;
}