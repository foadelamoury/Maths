#include "DraggablePoint.h"

DraggablePoint::DraggablePoint(const sf::Vector2f& position,const sf::RenderWindow& window)
{
	shape = sf::CircleShape(10);
	shape.setOrigin(10, 10);
	shape.setPosition(position);
}

void DraggablePoint::beginDrag(const sf::Vector2i& mousePos)
{
	isDragging = shape.getGlobalBounds().contains((sf::Vector2f)mousePos);
}

void DraggablePoint::drag(const sf::Vector2i& mousePos)
{
	if (!isDragging) return;
	shape.setPosition((sf::Vector2f)mousePos);
}

void DraggablePoint::endDrag()
{
	isDragging = false;
}

void DraggablePoint::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

bool DraggablePoint::isMouseOver(const sf::Vector2i& mousePos)
{
	isDragging = shape.getGlobalBounds().contains((sf::Vector2f)mousePos);
	return isDragging;
}

sf::Vector2f DraggablePoint::getPosition()
{
		return shape.getPosition();
}





