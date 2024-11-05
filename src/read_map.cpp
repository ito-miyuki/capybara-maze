#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> read_map(const std::string& filename) {
    std::ifstream file(filename);

    if(!file.is_open()) {
        std::cerr << "Error opening the file.\n";
        return {}; // return an empty vector
    }

    std::vector<std::vector<int>> map_data;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<int> row;
        for (char c : line) {
            if (c == '1')
                row.push_back(1);
            else if (c == '0')
                row.push_back(0);
        }
        map_data.push_back(row);
    }

    // for testing
    for (const auto& row : map_data) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }

    file.close();
    return map_data;
}