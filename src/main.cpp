#include "solong.hpp"

int main()
{
    sf::Vector2i playerPos(0,0);

    std::vector<std::vector<char>> map = read_map("map/map2.txt", playerPos);
    int rows = map.size(); // マップの行数
    int cols = map[0].size(); // マップの列数

    sf::RenderWindow window(sf::VideoMode(cols * tileSize, rows * tileSize), "My window");

    sf::Texture player_tex, floor_tex, grass_tex, item_tex, exit_tex;
    sf::Sprite player_sprite = put_texture(player_tex, "png/player.png");
    sf::Sprite floor_sprite = put_texture(floor_tex, "png/floor.png");
    sf::Sprite grass_sprite = put_texture(grass_tex, "png/grass.png");
    sf::Sprite item_sprite = put_texture(item_tex, "png/onigiri.png");
    sf::Sprite exit_sprite = put_texture(exit_tex, "png/exit.png");

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
            //movement(playerPos, map, event);
            movement(playerPos, map, event);
        }
        window.clear(sf::Color::Blue);

        for (int row = 0; row < map.size(); ++row) {
            for (int col = 0; col < map[row].size(); col++) {
                floor_sprite.setPosition((col * tileSize), row * tileSize);
                window.draw(floor_sprite);
                if (map[row][col] == '1') {
                    grass_sprite.setPosition(col * tileSize, row * tileSize);
                    window.draw(grass_sprite);
                }
                else if (map[row][col] == 'C') {
                    item_sprite.setPosition(col * tileSize, row * tileSize);
                    window.draw(item_sprite);
                }
                else if (map[row][col] == 'E') {
                    exit_sprite.setPosition(col * tileSize, row * tileSize);
                    window.draw(exit_sprite);
                }
            }
        }
        player_sprite.setPosition(playerPos.x * tileSize, playerPos.y * tileSize);
        window.draw(player_sprite);
        window.display();
    }
    return 0;
}