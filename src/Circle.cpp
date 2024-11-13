#include "Circle.h"




    Circle::Circle(float radius, sf::Color color) {
        shape.setRadius(radius);
        shape.setFillColor(color);
        shape.setOrigin(radius, radius);
        target = { 0, 0 };
    }

    void Circle::follow(const sf::Vector2f& newTarget, float speed, float minDistance) {
        target = newTarget;
        if (distance(shape.getPosition(), target) > minDistance) {
            shape.setPosition(lerp(shape.getPosition(), target, speed));
        }
    }

    sf::Vector2f Circle::lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t) {
        return start + t * (end - start);
    }

    float Circle::distance(const sf::Vector2f& a, const sf::Vector2f& b)
    {
        return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
    }
