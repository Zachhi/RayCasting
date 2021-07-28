#ifndef WALL_H
#define WALL_H
#define _USE_MATH_DEFINES //for pi

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <stdlib.h> 
#include <math.h>
#include "line.h"

class Wall {
private:
	sf::Vector2f p1, p2;
	Line line;
public:
	Wall(sf::Vector2f p1, sf::Vector2f p2); //constructor
	~Wall(); //destructor

	sf::Vector2f getPoint1() { return p1; }
	sf::Vector2f getPoint2() { return p2; }
	Line getLine() { return line; }
	void draw(sf::RenderWindow& window);
};

#endif  // WALL_H