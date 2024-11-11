#include <SFML/Graphics.hpp>

int main()
{
    sf::CircleShape circle;
    circle.setRadius(100);
    circle.setOrigin({circle.getRadius(), circle.getRadius()});
    circle.setPosition({1920u / 2, 1080u / 2});
    circle.setFillColor(sf::Color::Red);

    auto window = sf::RenderWindow({1920u, 1080u}, "CMake SFML Project");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
