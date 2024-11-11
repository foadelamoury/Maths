#include <SFML/Graphics.hpp>
#include "Quad.h" 

void DrawCircle(sf::CircleShape& circle, sf::RenderWindow& window)
{
    circle.setRadius(100);
    circle.setOrigin({ circle.getRadius(), circle.getRadius() });
    circle.setPosition({ window.getSize().x / 2.0f, window.getSize().y - 300.0f });
    circle.setFillColor(sf::Color::Red);
}

int main()
{
    Quad quad;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Easing");
    window.setFramerateLimit(144);

    sf::CircleShape circle;
    DrawCircle(circle, window);

    sf::Vector2f startPosition = circle.getPosition();
    sf::Vector2f targetPosition = startPosition;

    float moveTime = 0.0f;
    const float duration = 1.0f;  
    bool isMoving = false;

    while (window.isOpen())
    {
        for (sf::Event event; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.mouseButton.button == sf::Mouse::Left)
            {
                targetPosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                startPosition = circle.getPosition();
                moveTime = 0.0f;
                isMoving = true;
            }
        }

        if (isMoving)
        {
            moveTime += 1.0f / 144.0f;  

            if (moveTime < duration)
            {
                float newX = quad.easeIn(moveTime, startPosition.x, targetPosition.x - startPosition.x, duration);
                float newY = quad.easeIn(moveTime, startPosition.y, targetPosition.y - startPosition.y, duration);
                circle.setPosition(newX, newY);
            }
            else
            {
                circle.setPosition(targetPosition);
                isMoving = false;
            }
        }

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}
