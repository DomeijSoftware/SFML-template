// main.pcc
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define WINDOW_WIDTH 1920u
#define WINDOW_HEIGHT 1080u
constexpr float PI = 3.1415f;

// Enkel ortografisk projektion
sf::Glsl::Mat4 createOrthoProjection(float left, float right, float bottom, float top, float near, float far)
{
    float rl = right - left;
    float tb = top - bottom;
    float fn = far - near;

    float m[16] = {
        2.f / rl, 0.f, 0.f, 0.f,
        0.f, 2.f / tb, 0.f, 0.f,
        0.f, 0.f, -2.f / fn, 0.f,
        -(right + left) / rl, -(top + bottom) / tb, -(far + near) / fn, 1.f};

    return sf::Glsl::Mat4(m);
}

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
    sf::Glsl::Mat4 screenMatrix(tform.getMatrix());
    auto projection = createOrthoProjection(0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.f, -1.f, 1.f);

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

        sf::Vector2f screenSize = static_cast<sf::Vector2f>(window.getSize());
        shader.setUniform("iTime", clock.getElapsedTime().asSeconds());
        shader.setUniform("transform", sf::Glsl::Mat4(tform));
        shader.setUniform("iResolution", screenSize);
        window.clear();
        window.draw(screen, &shader);
        window.display();
    }
}
