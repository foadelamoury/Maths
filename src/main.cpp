#include "DraggablePoint.h"

sf::Color operator*(float value, sf::Color color) {
    return sf::Color(color.r * value, color.g * value, color.b * value, color.a * value);
}

template<class T>
T lerp(const T& start, const T& end, float alpha) {
    if (alpha < 0) return T(start);
    if (alpha > 1) return T(end);
    return (1 - alpha) * start + alpha * end;
}

void updateCurve(sf::VertexArray& curve, sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2) {
    int pointsCount = curve.getVertexCount();
    float t = 0;
    float delta = 1.f / (pointsCount - 1);

    for (size_t i = 0; i < pointsCount; i++) {
        sf::Vector2f p01 = lerp(p0, p1, t);
        sf::Vector2f p12 = lerp(p1, p2, t);
        curve[i].position = lerp(p01, p12, t);
        curve[i].color = lerp(sf::Color::Cyan, sf::Color::Magenta, t);
        t += delta;
    }
}

int main() {
    auto window = sf::RenderWindow({ 1920u, 1080u }, "Bezier");
    window.setFramerateLimit(144);
    DraggablePoint p0(sf::Vector2f(1000, 100), window);
    DraggablePoint p1(sf::Vector2f(800, 500), window);
    DraggablePoint p2(sf::Vector2f(1200, 500), window);

    sf::VertexArray line(sf::LineStrip, 3);
    sf::VertexArray curve(sf::LineStrip, 30);

    DraggablePoint* selectedPoint = nullptr;

    while (window.isOpen()) {
        for (auto event = sf::Event(); window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (p0.isMouseOver(sf::Mouse::getPosition(window))) {
                    selectedPoint = &p0;
                }
                else if (p1.isMouseOver(sf::Mouse::getPosition(window))) {
                    selectedPoint = &p1;
                }
                else if (p2.isMouseOver(sf::Mouse::getPosition(window))) {
                    selectedPoint = &p2;
                }

                if (selectedPoint) {
                    selectedPoint->beginDrag(sf::Mouse::getPosition(window));
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (selectedPoint) {
                    selectedPoint->endDrag();
                    selectedPoint = nullptr;
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && selectedPoint) {
            selectedPoint->drag(sf::Mouse::getPosition(window));
        }

        line[0].position = p0.getPosition();
        line[1].position = p1.getPosition();
        line[2].position = p2.getPosition();

        updateCurve(curve, p0.getPosition(), p1.getPosition(), p2.getPosition());

        window.clear();
        window.draw(curve);
        window.draw(line);
        p0.draw(window);
        p1.draw(window);
        p2.draw(window);
        window.display();
    }
}
