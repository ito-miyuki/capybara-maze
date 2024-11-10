#include "solong.hpp"

void movement(sf::Vector2i &playerPos, std::vector<std::vector<char>>& map, sf::Event event, Game& game) {
    int rows = map.size();
    int cols = map[0].size();
    
    if (event.type == sf::Event::KeyPressed && !game.checkGameOver(playerPos) && !game.getGoalReached()) {
        if (event.key.code == sf::Keyboard::W && playerPos.y > 0) {
            if (map[playerPos.y - 1][playerPos.x] == 'E') {
                if (game.canReachGoal())
                    playerPos.y -= 1;
            }
            else if (map[playerPos.y - 1][playerPos.x] != '1')
                playerPos.y -= 1;                
        }
        if (event.key.code == sf::Keyboard::S && playerPos.y < rows - 1) {
            if (map[playerPos.y + 1][playerPos.x] == 'E') {
                if (game.canReachGoal())
                    playerPos.y += 1;
            }
            else if (map[playerPos.y + 1][playerPos.x] != '1')
                playerPos.y += 1;
        }
        if (event.key.code == sf::Keyboard::A && playerPos.x > 0) {
            if (map[playerPos.y][playerPos.x - 1] == 'E') {
                if (game.canReachGoal())
                     playerPos.x -= 1;
            }
            else if (map[playerPos.y][playerPos.x - 1] != '1')
                playerPos.x -= 1;
        }
        if (event.key.code == sf::Keyboard::D && playerPos.x < cols - 1) {
            if (map[playerPos.y][playerPos.x + 1] == 'E') {
                if (game.canReachGoal())
                     playerPos.x += 1;
            }
            else if (map[playerPos.y][playerPos.x + 1] != '1')
                playerPos.x += 1;
        }
        if (map[playerPos.y][playerPos.x] == 'C') {
            map[playerPos.y][playerPos.x] = '0';
            game.collectItem();
        }
        if (map[playerPos.y][playerPos.x] == 'E' && game.getTotalItem() == game.getCollectedItem()) {
            game.displayGoalMessage();
        }
    }
}