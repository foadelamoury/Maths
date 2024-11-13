#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

sf::Vector2f cubicBezier(const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3, float t) {
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    sf::Vector2f point = uuu * p0;
    point += 3 * uu * t * p1;
    point += 3 * u * tt * p2;
    point += ttt * p3;

    return point;
}

float distance(const sf::Vector2f& a, const sf::Vector2f& b) {
    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bezier");
    window.setFramerateLimit(60);

    std::vector<sf::Vector2f> points = {
        sf::Vector2f(100, 500),
        sf::Vector2f(200, 100),
        sf::Vector2f(600, 100),
        sf::Vector2f(700, 500)
    };

    std::vector<sf::CircleShape> controlPoints;
    for (auto& point : points) {
        sf::CircleShape cp(5);
        cp.setFillColor(sf::Color::White);
        cp.setOrigin(5, 5);
        cp.setPosition(point);
        controlPoints.push_back(cp);
    }

    sf::CircleShape movingCircle(8);
    movingCircle.setFillColor(sf::Color::Cyan);
    movingCircle.setOrigin(8, 8);

    float t = 0.0f;
    bool moveAlongCurve = false;
    bool dragging = false;
    int draggedPointIndex = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                moveAlongCurve = true;
                t = 0.0f;
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
                for (size_t i = 0; i < points.size(); ++i) {
                    if (distance(controlPoints[i].getPosition(), mousePos) < 10.0f) {
                        dragging = true;
                        draggedPointIndex = i;
                        break;
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                dragging = false;
                draggedPointIndex = -1;
            }
        }

        if (dragging && draggedPointIndex != -1) {
            points[draggedPointIndex] = (sf::Vector2f)sf::Mouse::getPosition(window);
            controlPoints[draggedPointIndex].setPosition(points[draggedPointIndex]);
        }

        if (moveAlongCurve) {
            t += 0.005f;
            if (t > 1.0f) {
                t = 1.0f;
                moveAlongCurve = false;
            }
            movingCircle.setPosition(cubicBezier(points[0], points[1], points[2], points[3], t));
        }

        window.clear();

        sf::Vertex line[] = {
            sf::Vertex(points[0], sf::Color::White),
            sf::Vertex(points[1], sf::Color::White),
            sf::Vertex(points[2], sf::Color::White),
            sf::Vertex(points[3], sf::Color::White)
        };
        window.draw(line, 4, sf::LinesStrip);

        for (const auto& cp : controlPoints) {
            window.draw(cp);
        }

        sf::VertexArray bezierCurve(sf::LineStrip);
        for (float i = 0; i <= 1.0f; i += 0.01f) {
            bezierCurve.append(sf::Vertex(cubicBezier(points[0], points[1], points[2], points[3], i), sf::Color::Cyan));
        }
        window.draw(bezierCurve);

        if (moveAlongCurve) {
            window.draw(movingCircle);
        }

        window.display();
    }

    return 0;
}
