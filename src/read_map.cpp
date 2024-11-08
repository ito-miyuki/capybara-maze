#include "solong.hpp"

std::vector<std::vector<char>> read_map(const std::string& filename, sf::Vector2i& playerPos) {
    std::ifstream file(filename);

    if(!file.is_open()) {
        std::cerr << "Error opening the file.\n";
        return {}; // return an empty vector
    }

    std::vector<std::vector<char>> map_data;
    std::string line;

    int row = 0;
    while (std::getline(file, line)) {
        std::vector<char> row_data;
        for (int col = 0; col < line.size(); ++col) {
            char c = line[col];
            row_data.push_back(c);

            // プレイヤー位置が見つかったら、その座標を保存
            if (c == 'P') {
                playerPos = sf::Vector2i(col, row);
            }
        }
        map_data.push_back(row_data);
        ++row;
    }

    // for testing
    for (const auto& row : map_data) {
        for (char cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }

    file.close();
    return map_data;
}