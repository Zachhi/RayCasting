#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <stdlib.h> 
#include <math.h>

class Line
{
private:
	sf::Vector2f p1, p2;
	int thickness;
	float angle;
	sf::RectangleShape lineRect;
public:
	Line(sf::Vector2f point1, sf::Vector2f point2, int thickness);
	Line(sf::Vector2f point1, float angle, int thickness);
	~Line();
	void draw(sf::RenderWindow& window);
	void move(sf::Vector2f point);
	void setLength(float len);
	void setEndPoint(sf::Vector2f point);
	sf::Vector2f getPoint1() { return p1; }
	sf::Vector2f getPoint2() { return p2; }
	int getThickness() { return thickness; }
	sf::RectangleShape& getRect() { return lineRect; }
	float getMagnitude(sf::Vector2f px);
	void calculateEndPoints();
};

#endif  // LINE_H