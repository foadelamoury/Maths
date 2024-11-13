#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
class Circle {
public:
    sf::CircleShape shape;
    sf::Vector2f target;

    Circle(float radius, sf::Color color);

    void follow(const sf::Vector2f& newTarget, float speed, float minDistance);

private:
    sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t);

    float distance(const sf::Vector2f& a, const sf::Vector2f& b);
};