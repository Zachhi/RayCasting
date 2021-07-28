#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdlib.h> 
#include <math.h>
#include "lightRay.h"

class LightSource
{
public:
	LightSource(sf::Vector2f position, int rayCount);
	~LightSource();
	void move(sf::Vector2f position);
	void checkWalls(std::vector<Wall>& walls);
	void drawAll(sf::RenderWindow& window);
	void drawCollisions(sf::RenderWindow& window);
	void setNumRay(int num);

private:
	sf::Vector2f position;
	int rayCount;
	std::vector<LightRay> lightRays;
};



#endif  // LIGHTSOURCE_H