#include <SFML/Graphics.hpp>
sf::Color operator*(float value, sf::Color color)
{
    return sf::Color(color.r * value, color.g * value, color.b * value, color.a * value);
}

template<class T>
T lerp(const T& start, const T& end, float alpha)
{
    if (alpha < 0) return T(start);
    if (alpha > 1) return T(end);

    return (1 - alpha) * start + alpha * end;
}

//
//sf::Color lerp(const sf::Color& start, const sf::Color& end, float alpha)
//{
//    return (1 - alpha) * start + alpha * end;
//}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Template!");
    sf::CircleShape shape(20);
    shape.setOrigin(20, 20);


    sf::Vector2f position(20, 20);
    sf::Vector2f targetPosition(position);
    sf::Vector2f startPosition(position);


    sf::Color color(sf::Color::Red);
    sf::Color targetColor(sf::Color::Yellow);
    sf::Color startColor(sf::Color::Red);


    sf::Clock clock;
    float time;

    float d = 0.5;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonReleased)
            {
                targetPosition = (sf::Vector2f)sf::Mouse::getPosition(window);
                startPosition = position;
                clock.restart();
            }
        }

        time = clock.getElapsedTime().asSeconds();

        float alpha = time / d;

        position = lerp(startPosition, targetPosition, alpha);
        color = lerp(sf::Color::Cyan, sf::Color::Magenta, alpha);

        shape.setFillColor(color);
        shape.setPosition(position);

        window.clear();

        window.draw(shape);

        window.display();
    }

    return 0;
}