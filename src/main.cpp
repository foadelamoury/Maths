#include "Circle.h"
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Trailing Day");
    window.setFramerateLimit(60);

    std::vector<Circle> circles;
    int numCircles = 5;
    float radius = 10.0f;
    float lerpSpeed = 0.4f;
    float spacing = 50.0f; 

    for (int i = 0; i < numCircles; i++) {
        circles.emplace_back(radius, sf::Color::White);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
        circles[0].follow(mousePosition, lerpSpeed, spacing);

        for (int i = 1; i < numCircles; i++) {
            circles[i].follow(circles[i - 1].shape.getPosition(), lerpSpeed, spacing);
        }

        window.clear();
        for (const auto& circle : circles) {
            window.draw(circle.shape);
        }
        window.display();
    }

    return 0;
}
