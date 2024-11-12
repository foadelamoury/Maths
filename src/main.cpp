#include <SFML/Graphics.hpp>
#include <cmath>

#define PI 3.14159265f

void updateArc(sf::ConvexShape& shape, const sf::Vector2f& center, float radius, float startAngle, float endAngle)
{
    int pointCount = shape.getPointCount() - 1;
    float angleStep = (endAngle - startAngle) / (pointCount - 1);

    for (int i = 0; i < pointCount; ++i)
    {
        float angle = startAngle + i * angleStep;
        float radian = angle * (PI / 180.f);

        float x = center.x + radius * std::cos(radian);
        float y = center.y + radius * std::sin(radian);

        shape.setPoint(i, sf::Vector2f(x, y));
    }

    shape.setPoint(pointCount, center);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pac-Man Mouth Animation");
    window.setFramerateLimit(60);

    sf::ConvexShape shape(51);
    shape.setFillColor(sf::Color::Yellow);

    sf::Vector2f center(200, 200);
    float radius = 100.0f;

    shape.setOrigin(center);
    shape.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    sf::Clock clock;
    float startAngle = 10;
    float endAngle = 340;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            startAngle = 10;  
            endAngle = 340;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            startAngle = -160;  
            endAngle = 170;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            startAngle = -80;  
            endAngle = 250;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            startAngle = 60; 
            endAngle = -240;
        }

        float time = clock.getElapsedTime().asSeconds();
        float angleOffset = -10 + 5 * std::sin(time * 5); 
       
        if(startAngle == 60 && endAngle == -240)
            angleOffset = 26 + 5 * std::sin(time * 5);


        updateArc(shape, center, radius, startAngle + angleOffset, endAngle - angleOffset);

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
