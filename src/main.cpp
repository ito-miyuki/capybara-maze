#include "solong.hpp"

int main()
{
    sf::Vector2i playerPos(0,0);
    sf::Vector2i enemyStartPos(0,0);
    int totalItems = 0;

    std::string mapPath = "map/map";
    std::vector<std::vector<char>> map = read_map("map/map1.txt", playerPos, enemyStartPos, totalItems);
    Game game(totalItems, enemyStartPos);

    int rows = map.size(); // マップの行数
    int cols = map[0].size(); // マップの列数

    sf::RenderWindow window(sf::VideoMode(cols * tileSize, rows * tileSize), "Capybara maze");

    sf::Texture player_tex, floor_tex, grass_tex, item_tex, exit_tex, enermy_tex;
    sf::Sprite player_sprite = put_texture(player_tex, "png/player.png");
    sf::Sprite floor_sprite = put_texture(floor_tex, "png/floor.png");
    sf::Sprite grass_sprite = put_texture(grass_tex, "png/grass.png");
    sf::Sprite item_sprite = put_texture(item_tex, "png/onigiri.png");
    sf::Sprite exit_sprite = put_texture(exit_tex, "png/exit.png");
    sf::Sprite enermy_sprite = put_texture(enermy_tex, "png/enermy.png");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                if (game.getGoalReached()) {
                    game.nextLevel(enemyStartPos);
                    if (game.getCurrentLevel() > game.getMaxLevel()) {
                        std::cout << "Game Completed!\n";
                        //window.close();
                    } else {
                        map = read_map(mapPath + std::to_string(game.getCurrentLevel()) + ".txt", playerPos, enemyStartPos, totalItems);
                        rows = map.size(); // マップの行数を更新
                        cols = map[0].size();
                        window.setSize(sf::Vector2u(cols * tileSize, rows * tileSize));

                        game.resetEnemyPosition(enemyStartPos);
                    }
                }
            }
            movement(playerPos, map, event, game);
        }
        
        if (game.checkGameOver(playerPos)) {
            game.update(window);
        } else {
            window.clear(sf::Color::Blue);
            game.moveEnemy(map);
        }

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

        if (!(enemyStartPos.y == 0 && enemyStartPos.x == 0)) {
            enermy_sprite.setPosition(game.getEnemyPos().x * tileSize, game.getEnemyPos().y * tileSize);
            window.draw(enermy_sprite);
        }

        game.update(window);
        window.display();
    }
    return 0;
}