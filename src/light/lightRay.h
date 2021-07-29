#ifndef LIGHTRAY_H
#define LIGHTRAY_H
#include <SFML/Graphics.hpp>
#include "../line/line.h"
#include "../wall/wall.h"

class LightRay
{
public:
	LightRay(sf::Vector2f position, float angle);
	void move(sf::Vector2f position);
	float checkCollision(Wall& wall, float currMinimum);
	void resetRays();
	void drawAll(sf::RenderWindow& window);
	void drawCollisions(sf::RenderWindow& window);
	Line getLine() { return line; }
private:
	Line line;
	sf::Vector2f position;
	float angle;
	float currDis;
	float disToBorders;
};



#endif  // LIGHTRAY_H