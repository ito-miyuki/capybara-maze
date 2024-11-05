#include <SFML/Window.hpp>
#include "SFML/Graphics/RenderWindow.hpp"

std::vector<std::vector<int>> read_map(const std::string& filename);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    read_map("map/map1.txt");

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
        window.display();
    }

    return 0;
}