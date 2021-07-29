#include <math.h>
#include "lightRay.h"
#include <iostream>
#define SX 2800
#define SY 1600
#define RAD 3.14159265 / 180.0

LightRay::LightRay(sf::Vector2f position, float angle) : line(position, angle, 1.5)
{
	this->position = position;
	this->angle = angle;
    disToBorders = sqrt(pow(SX, 2) + pow(SY, 2));
    currDis = disToBorders;
}
void LightRay::move(sf::Vector2f position) //move the ray to new position
{
	this->position = position;
	line.move(position);
}
void LightRay::resetRays() //reset rays when walls are cleared
{
    line.setLength(disToBorders);
    currDis = disToBorders;
}
float LightRay::checkCollision(Wall& wall, float currMinimum) //check if and where the light ray will collide with the wall
{
    float x1 = line.getPoint1().x;
    float y1 = line.getPoint1().y;
    float x2 = line.getPoint2().x;
    float y2 = line.getPoint2().y;
    float hypo = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

    float x3 = wall.getPoint1().x;
    float y3 = wall.getPoint1().y;
    float x4 = wall.getPoint2().x;
    float y4 = wall.getPoint2().y;

    float numerator1 = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4);
    float numerator2 = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3));
    float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (denominator != 0)
    {
        const float t = numerator1 / denominator;
        const float u = numerator2 / denominator;
        if (0 < u && 0 < t && u < 1)
        {
            //std::cout << t << " " << u << std::endl;
            float intersection_x = x1 + t * (x2 - x1);
            float intersection_y = y1 + t * (y2 - y1);
            sf::Vector2f intersections(intersection_x, intersection_y);
            float hold = line.getMagnitude(intersections);
            if (hold <= currMinimum)
            {
                line.setEndPoint(intersections);
                currMinimum = hold;
                currDis = currMinimum;
                return currMinimum;
            }


        }
        else
        {
            if (currMinimum > disToBorders)
            {
                line.setLength(disToBorders);
                currMinimum = (disToBorders);
                currDis = (disToBorders);
            }
        }
    }
    else
    {
        if (currMinimum > disToBorders)
        {
            line.setLength(disToBorders);
            currMinimum = (disToBorders);
            currDis = (disToBorders);
        }
    }
    return currMinimum;
}

void LightRay::drawAll(sf::RenderWindow& window) //draw the line when we have to draw every ray
{
    sf::Color lB(204, 255, 229);
    if (currDis == disToBorders)
        line.getRect().setFillColor(lB);
    else
        line.getRect().setFillColor(sf::Color::White);

	line.draw(window);
}
void LightRay::drawCollisions(sf::RenderWindow& window) //draw the line when we only draw intersection rays
{
    sf::Color lB(204, 255, 229);
    if (currDis == disToBorders)
        line.getRect().setFillColor(lB);
    else
        line.getRect().setFillColor(sf::Color::White);

    if (currDis != disToBorders)
        line.draw(window);
}