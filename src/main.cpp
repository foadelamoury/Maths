#include <SFML/Graphics.hpp>





/// <summary>
/// This is the equation to find any point in a line: x= t(x1 -x0) + x0 = (1-t)x0 + tx1
///                                                   y= t(y1 -y0) + y0 = (1-t)y0 + ty1
/// </summary>
/// <param name="start">x0</param>
/// <param name="end">x1</param>
/// <param name="alpha">t</param>
/// <returns></returns>
template<class T>
T lerp(const T& start, const T& end, float alpha)
{
    if (alpha < 0) return T(start);
    if (alpha > 1) return T(end);

    return (1 - alpha) * start + alpha * end;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Template!");
    sf::CircleShape shape(20);
    shape.setOrigin(20, 20);
    shape.setFillColor(sf::Color::Green);

    //float alpha = 0.002;
    float speed = 3;

    sf::Vector2f position;

    sf::Clock clock;
    float deltaTime;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2f tragetPosition = (sf::Vector2f)sf::Mouse::getPosition(window);

        position = lerp(position, tragetPosition, speed * deltaTime);


        shape.setPosition(position);

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}