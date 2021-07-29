#ifndef WALL_H
#define WALL_H
#define _USE_MATH_DEFINES //for pi
#include "../line/line.h"

class Wall {
private:
	sf::Vector2f p1, p2; //coordinates for both points
	Line line; //the wall will just be a line between the two points
public:
	Wall(sf::Vector2f p1, sf::Vector2f p2); //constructor
	~Wall(); //destructor

	sf::Vector2f getPoint1() { return p1; } //return first point
	sf::Vector2f getPoint2() { return p2; } //return second point
	Line getLine() { return line; } //return the line object
	void draw(sf::RenderWindow& window); //draw the wall
};

#endif  // WALL_H