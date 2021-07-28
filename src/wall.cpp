#include "wall.h"
#include <iostream>
Wall::Wall(sf::Vector2f p1, sf::Vector2f p2) : line(p1, p2, 7)
{
	this->p1 = p1;
	this->p2 = p2;
}
Wall::~Wall()
{

}

void Wall::draw(sf::RenderWindow& window)
{
	line.draw(window);
}