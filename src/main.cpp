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
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "TheArc");
    window.setFramerateLimit(144);

    sf::ConvexShape shape(51);  
    shape.setFillColor(sf::Color::Green);

    sf::Vector2f center(400, 400); 

    shape.setOrigin(center);
    shape.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    updateArc(shape, center, 200, -45, 45);  

    while (window.isOpen())
    {
        for (sf::Event event; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
