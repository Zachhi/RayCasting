#include "lightSource.h"
#include <iostream>
#define SX 1800
#define SY 1600
LightSource::LightSource(sf::Vector2f position, int rayCount)
{
	this->rayCount = rayCount;
	this->position = position;
	for (int i = 1; i < this->rayCount + 1; i++)
	{
		LightRay ray(this->position, (360.0 / this->rayCount) * i);
		lightRays.push_back(ray);
	}
}
LightSource::~LightSource()
{

}
void LightSource::setNumRay(int num) //update the number of rays the source has
{
	rayCount = num;
	lightRays.clear();
	for (int i = 1; i < this->rayCount + 1; i++)
	{
		LightRay ray(this->position, (360.0 / this->rayCount) * i);
		lightRays.push_back(ray);
	}
}
void LightSource::move(sf::Vector2f position) //move the source to new position
{
	for (int i = 0; i < rayCount; i++)
	{
		lightRays[i].move(position);
	}
}
void LightSource::checkWalls(std::vector<Wall>& walls) //update it with the walls 
{
	float currMinimum;
	for (auto& ray : lightRays)
	{
		currMinimum = 9999999;
		for (auto& wall : walls)
		{
			float hold = ray.checkCollision(wall, currMinimum);
			if (hold < currMinimum)	
				currMinimum = hold;
		}
	}
	if (walls.size() < 1) //reset rays if no walls
	{
		for (int i = 0; i < rayCount; i++)
			lightRays[i].resetRays();
	}
}
void LightSource::drawAll(sf::RenderWindow& window)
{
	for (int i = 0; i < rayCount; i++)
	{
		lightRays[i].drawAll(window);
	}
}
void LightSource::drawCollisions(sf::RenderWindow& window)
{
	for (int i = 0; i < rayCount; i++)
	{
		lightRays[i].drawCollisions(window);
	}
}