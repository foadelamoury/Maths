#include <SFML/Graphics.hpp>

float dot(sf::Vector2f v1, sf::Vector2f v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

sf::Vector2f project(sf::Vector2f v1, sf::Vector2f v2)
{
	float dot1 = dot(v1, v2);
	float dot2 = dot(v2, v2);

	return (dot1 / dot2) * v2;
}

class DraggablePoint {

	sf::CircleShape shape;
	bool isDragging;
public:
	DraggablePoint(const sf::Vector2f& position)
	{
		shape = sf::CircleShape(10);
		shape.setOrigin(10, 10);
		shape.setPosition(position);
	}

	void beginDrag(const sf::Vector2i& mousePos)
	{
		isDragging = shape.getGlobalBounds().contains((sf::Vector2f)mousePos);
	}

	void drag(const sf::Vector2i& mousePos)
	{
		if (!isDragging) return;
		shape.setPosition((sf::Vector2f)mousePos);
	}

	void endDrag()
	{
		isDragging = false;
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}

	sf::Vector2f getPosition()
	{
		return shape.getPosition();
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Template!");
	DraggablePoint point0(sf::Vector2f(400, 100));
	DraggablePoint point1(sf::Vector2f(400, 500));

	sf::CircleShape point(10);
	point.setFillColor(sf::Color::Green);
	point.setOrigin(10, 10);

	sf::VertexArray line(sf::LineStrip, 2);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				point0.beginDrag(sf::Mouse::getPosition(window));
				point1.beginDrag(sf::Mouse::getPosition(window));
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				point0.endDrag();
				point1.endDrag();
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			point0.drag(sf::Mouse::getPosition(window));
			point1.drag(sf::Mouse::getPosition(window));
		}


		line[0].position = point0.getPosition();
		line[1].position = point1.getPosition();

		sf::Vector2f p0 = point0.getPosition();
		sf::Vector2f p1 = point1.getPosition();

		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);


		sf::Vector2f a = p1 - p0;
		sf::Vector2f b = mousePos - p0;

		sf::Vector2f proj = project(b, a);


		point.setPosition(proj + p0);

		window.clear();

		point0.draw(window);
		point1.draw(window);
		window.draw(line);
		window.draw(point);

		point.setPosition(400, 300);
		window.draw(point);

		window.display();
	}

	return 0;
}