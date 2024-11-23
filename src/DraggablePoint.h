#pragma once

#include <SFML/Graphics.hpp>

class DraggablePoint
{
protected:
	sf::CircleShape shape;
	bool isDragging;	
public:
	DraggablePoint(const sf::Vector2f& position);
	void beginDrag(const sf::Vector2i& mousePos);
	void drag(const sf::Vector2i& mousePos);
	void endDrag();
	DraggablePoint(const sf::Vector2f& position, const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

	bool isMouseOver(const sf::Vector2i& mousePos);
	sf::Vector2f getPosition();

};

