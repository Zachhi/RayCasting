#include <math.h>
#include "line.h"
#include <iostream>
#define PI 3.14159265
#define RAD 3.14159265 / 180.0
#define SX 2800
#define SY 1600

Line::Line(sf::Vector2f point1, sf::Vector2f point2, int thickness) //for walls
{
	p1 = point1;
	p2 = point2;
	this->thickness = thickness;

	//do calculations for angle
	this->angle =  atan2((point2.y - point1.y) , (point2.x - point1.x)) * 180 / PI;

	//set the properties for the rect
	sf::RectangleShape tempRect(sf::Vector2f(sqrt(pow(float(point2.x - point1.x), 2) + pow(float(point2.y - point1.y), 2)), thickness));
	lineRect = tempRect;
	sf::Color lB(213,213,213);
	lineRect.setFillColor(sf::Color::Red);
	lineRect.setOrigin(0, thickness / 2);
	lineRect.setPosition(point1);
	lineRect.rotate(angle);
}
Line::Line(sf::Vector2f point1, float angle, int thickness) //for light rays
{
	p1 = point1;
	this->thickness = thickness;
	this->angle = angle;

	//set the properties for the rect
	sf::RectangleShape tempRect(sf::Vector2f(sqrt(pow(float(SX), 2) + pow(float(SY), 2)), thickness));
	lineRect = tempRect;
	sf::Color lB(204,255,229);
	lineRect.setFillColor(lB);
	lineRect.setOrigin(0, thickness / 2);
	lineRect.setPosition(point1);
	lineRect.rotate(angle);

	calculateEndPoints();
}
Line::~Line()
{

}

void Line::move(sf::Vector2f point) //move the line
{
	p1 = point;
	calculateEndPoints();
	lineRect.setPosition(p1);
}
void Line::setLength(float len) //set the lines length
{
	lineRect.setSize(sf::Vector2f(len, thickness));
}
void Line::setEndPoint(sf::Vector2f point) //set the lines endpoint. will need when we calculate the lines intersections
{
	p2 = point;
	lineRect.setSize(sf::Vector2f(sqrt(pow(float(p2.x - p1.x), 2) + pow(float(p2.y - p1.y), 2)), thickness));
}
void Line::calculateEndPoints() //calculate the endpoint depending on the first point, angle, and length of line
{
	float hypotenuse = sqrt(pow(lineRect.getSize().x, 2) + pow(lineRect.getScale().y, 2));
	if (angle >= 0 && angle <= 90)
	{
		p2.x = p1.x + cos(angle * RAD) * hypotenuse;
		p2.y = p1.y + sin(angle * RAD) * hypotenuse;
	}
	else if (angle >= 90 && angle <= 180)
	{
		p2.x = p1.x - cos((180 - angle) * RAD) * hypotenuse;
		p2.y = p1.y + sin((180 - angle) * RAD) * hypotenuse;
	}
	else if (angle >= 180 && angle <= 270)
	{
		p2.x = p1.x - cos((angle - 180) * RAD) * hypotenuse;
		p2.y = p1.y - sin((angle - 180) * RAD) * hypotenuse;
	}
	else
	{
		p2.x = p1.x + cos((360 - angle) * RAD) * hypotenuse;
		p2.y = p1.y - sin((360 - angle) * RAD) * hypotenuse;
	}
}
float Line::getMagnitude(sf::Vector2f px) //return length of line
{
	float magnitude = (sqrt(pow(float(px.x - p1.x), 2) + pow(float(px.y - p1.y), 2)));
	return magnitude;
}

void Line::draw(sf::RenderWindow& window) //draw line
{
	window.draw(lineRect);
}