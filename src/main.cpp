#include <SFML/Graphics.hpp>
#include <cmath>

constexpr float PI = 3.14159265f;

float toRadians(float degrees) {
    return degrees * PI / 180.0f;
}

bool isInFOV(const sf::Vector2f& positionA, const sf::Vector2f& positionB, float distanceLimit, float angleLimit, float rotation) {
    sf::Vector2f direction = positionA - positionB;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > distanceLimit) {
        return false;
    }

    float angleToA = std::atan2(direction.y, direction.x) * 180 / PI;
    float angleDiff = std::abs(angleToA - rotation);

    if (angleDiff > 180.0f) {
        angleDiff = 360.0f - angleDiff;
    }

    return angleDiff <= angleLimit / 2.0f;
}

void drawFOV(sf::RenderWindow& window, const sf::Vector2f& position, float rotation, float radius, float angle, const sf::Color& color) {
    sf::VertexArray fovCone(sf::TriangleFan);
    fovCone.append(sf::Vertex(position, color));

    for (int i = -angle / 2; i <= angle / 2; i += 1) {
        float rad = toRadians(rotation + i);
        sf::Vector2f endpoint = position + sf::Vector2f(std::cos(rad) * radius, std::sin(rad) * radius);
        fovCone.append(sf::Vertex(endpoint, color));
    }

    window.draw(fovCone);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "FOV");
    window.setFramerateLimit(60);

    sf::CircleShape circleA(20);
    circleA.setFillColor(sf::Color::Red);
    circleA.setPosition(400, 300);
    circleA.setOrigin(20, 20);

    sf::CircleShape circleB(20);
    circleB.setFillColor(sf::Color::Blue);
    circleB.setPosition(200, 150);
    circleB.setOrigin(20, 20);

    float fovRadius = 100.0f;
    float fovAngle = 60.0f;
    float fovRotation = 0.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            circleB.move(0, -2);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            circleB.move(0, 2);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            circleB.move(-2, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            circleB.move(2, 0);
        }

        sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
        sf::Vector2f direction = mousePosition - circleB.getPosition();
        fovRotation = std::atan2(direction.y, direction.x) * 180 / PI;

        bool targetInFOV = isInFOV(circleA.getPosition(), circleB.getPosition(), fovRadius, fovAngle, fovRotation);
        sf::Color fovColor = targetInFOV ? sf::Color::Green : sf::Color(0, 255, 255, 100);

        window.clear();
        window.draw(circleA);
        window.draw(circleB);

        drawFOV(window, circleB.getPosition(), fovRotation, fovRadius, fovAngle, fovColor);

        window.display();
    }

    return 0;
}
