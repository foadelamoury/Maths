#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Circle {
public:
    sf::CircleShape shape;
    sf::Vector2f target;

    Circle(float radius, sf::Color color) {
        shape.setRadius(radius);
        shape.setFillColor(color);
        shape.setOrigin(radius, radius);  // Center the circle
        target = { 0, 0 };
    }

    void follow(const sf::Vector2f& newTarget, float speed, float minDistance) {
        target = newTarget;
        if (distance(shape.getPosition(), target) > minDistance) {
            shape.setPosition(lerp(shape.getPosition(), target, speed));
        }
    }

private:
    sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t) {
        return start + t * (end - start);
    }

    float distance(const sf::Vector2f& a, const sf::Vector2f& b) {
        return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
    }
};

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
