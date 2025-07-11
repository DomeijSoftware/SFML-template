// main.pcc
#include <iostream>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1920u
#define WINDOW_HEIGHT 1080u
constexpr float PI = 3.1415f;

int main()
{
    const sf::Vector2 windowDimensions = sf::Vector2(WINDOW_WIDTH, WINDOW_HEIGHT);
    auto window = sf::RenderWindow(sf::VideoMode(windowDimensions), "Window");
    window.setFramerateLimit(60);
    // window.setView(sf::View(sf::Rect<float>({-1.f, -1.f}, {static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT)})));
    sf::RectangleShape screen({WINDOW_WIDTH, WINDOW_HEIGHT});
    sf::Image blankImage({2, 2}, sf::Color::White);
    sf::Texture blankTexture;
    bool loadedTexture = blankTexture.loadFromImage(blankImage);
    (void)loadedTexture;
    screen.setTexture(&blankTexture);

    sf::Transform tform = screen.getTransform();

    sf::Shader shader;
    if (!shader.loadFromFile("../../shaders/Vert/test.vert", "../../shaders/Frag/test.frag"))
    {
        std::cout << "Error loading shader" << std::endl;

        return -1;
    }

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        shader.setUniform("iTime", clock.getElapsedTime().asSeconds());
        shader.setUniform("transform", sf::Glsl::Mat4(tform));
        shader.setUniform("iResolution", sf::Vector2f{WINDOW_WIDTH, WINDOW_HEIGHT});
        window.clear();
        window.draw(screen, &shader);
        window.display();
    }
}
