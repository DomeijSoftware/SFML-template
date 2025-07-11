// main.pcc
#include <iostream>
#include <SFML/Graphics.hpp>

constexpr float PI = 3.1415f;

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(60);
    sf::CircleShape circle(100.f);
    sf::Texture texture;
    if (!texture.loadFromFile("../../textures/John-Monsterhunter.jpg", false))
    {
        std::cout << "Error loading textures" << std::endl;

        return -1;
    }

    circle.setTexture(&texture);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.draw(circle);
        window.display();
    }
}
