#include <SFML/Graphics.hpp>
#include <cmath>

float distance(const sf::Vector2f& a, const sf::Vector2f& b) {
    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

sf::Vector2f reflectPoint(const sf::Vector2f& point, const sf::Vector2f& lineStart, const sf::Vector2f& lineEnd) {
    sf::Vector2f lineDir = lineEnd - lineStart;
    float length = distance(lineStart, lineEnd);
    lineDir /= length;

    sf::Vector2f lineToPoint = point - lineStart;
    float projectionLength = lineToPoint.x * lineDir.x + lineToPoint.y * lineDir.y;
    sf::Vector2f projection = lineDir * projectionLength;

    sf::Vector2f perpendicular = lineToPoint - projection;
    return point - perpendicular * 2.0f;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mirroring with Offset");
    window.setFramerateLimit(60);

    sf::Vector2f linePoints[2] = { {200, 300}, {600, 300} };
    sf::Vector2f trianglePoints[3] = { {300, 400}, {400, 200}, {500, 400} };

    sf::CircleShape lineCircles[2], triangleCircles[3];
    for (int i = 0; i < 2; ++i) {
        lineCircles[i].setRadius(5);
        lineCircles[i].setFillColor(sf::Color::White);
        lineCircles[i].setOrigin(5, 5);
        lineCircles[i].setPosition(linePoints[i]);
    }
    for (int i = 0; i < 3; ++i) {
        triangleCircles[i].setRadius(5);
        triangleCircles[i].setFillColor(sf::Color::Yellow);
        triangleCircles[i].setOrigin(5, 5);
        triangleCircles[i].setPosition(trianglePoints[i]);
    }

    bool dragging = false;
    int draggedPointIndex = -1;
    bool isLinePoint = false;

    float offsetDistance = 50.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);

                for (int i = 0; i < 2; ++i) {
                    if (distance(mousePos, linePoints[i]) < 10.0f) {
                        dragging = true;
                        draggedPointIndex = i;
                        isLinePoint = true;
                        break;
                    }
                }
                if (!dragging) {
                    for (int i = 0; i < 3; ++i) {
                        if (distance(mousePos, trianglePoints[i]) < 10.0f) {
                            dragging = true;
                            draggedPointIndex = i;
                            isLinePoint = false;
                            break;
                        }
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                dragging = false;
                draggedPointIndex = -1;
            }
        }

        if (dragging) {
            sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
            if (isLinePoint) {
                linePoints[draggedPointIndex] = mousePos;
                lineCircles[draggedPointIndex].setPosition(mousePos);
            }
            else {
                trianglePoints[draggedPointIndex] = mousePos;
                triangleCircles[draggedPointIndex].setPosition(mousePos);
            }
        }

        sf::Vector2f reflectedTrianglePoints[3];
        for (int i = 0; i < 3; ++i) {
            reflectedTrianglePoints[i] = reflectPoint(trianglePoints[i], linePoints[0], linePoints[1]);
        }

        sf::Vector2f lineDir = linePoints[1] - linePoints[0];
        float lineLength = distance(linePoints[0], linePoints[1]);
        lineDir /= lineLength;

        sf::Vector2f offsetDir(-lineDir.y, lineDir.x); 
        offsetDir *= offsetDistance;

        for (int i = 0; i < 3; ++i) {
            reflectedTrianglePoints[i] += offsetDir;
        }

        window.clear();

        sf::Vertex line[] = {
            sf::Vertex(linePoints[0], sf::Color::White),
            sf::Vertex(linePoints[1], sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);

        for (const auto& circle : lineCircles) {
            window.draw(circle);
        }

        sf::VertexArray triangle(sf::Triangles);
        for (const auto& point : trianglePoints) {
            triangle.append(sf::Vertex(point, sf::Color::Yellow));
        }
        window.draw(triangle);

        for (const auto& circle : triangleCircles) {
            window.draw(circle);
        }

        sf::VertexArray reflectedTriangle(sf::Triangles);
        for (const auto& point : reflectedTrianglePoints) {
            reflectedTriangle.append(sf::Vertex(point, sf::Color::Green));
        }
        window.draw(reflectedTriangle);

        window.display();
    }

    return 0;
}
