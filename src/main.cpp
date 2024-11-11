#include <SFML/Graphics.hpp>
#include <iostream>

#define PI (22/7.0f)


float Jump(float t, float d)
{
    return (-4 / d / d) * t * t + (4 / d) * t;
}

int main()
{
    int duration = 1;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Just Jump");
    window.setFramerateLimit(60);

    sf::CircleShape circle;
    circle.setRadius(100);
    circle.setOrigin({ circle.getRadius(), circle.getRadius() });
    
    circle.setPosition({ window.getSize().x / 2.0f, window.getSize().y - 300.0f });
    circle.setFillColor(sf::Color::Red);

    bool isJumping = false;
    float time = 0.0f;

    while (window.isOpen())
    {
        for (sf::Event event; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.key.code == sf::Keyboard::Space && isJumping == false)
            {
                isJumping = true;
                time = 0.0f;
            }
        }

        if (isJumping == true)
        {
            time += 1.0f / 60;  

            float jumpDistance = Jump(time, duration);

            circle.setPosition(circle.getPosition().x, window.getSize().y - 300.0f - jumpDistance * 300.0f);

            if (time >= duration)
            {
                isJumping = false;
                circle.setPosition(circle.getPosition().x, window.getSize().y - 300.0f);
            }
        }

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}

