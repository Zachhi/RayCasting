#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <stdlib.h> 
#include <math.h>
#include <iostream>
#include "wall.h"
#include "lightSource.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(2800, 1600), "RayCasting", sf::Style::Fullscreen);
	sf::Event event;
	std::vector<Wall> wallVector;
	Wall testWall(sf::Vector2f(400, 400), sf::Vector2f(800, 800));
	//wallVector.push_back(testWall);
	sf::Vector2f tempStartingPoint;
	sf::Vector2f tempEndingPoint;
	sf::Vector2i mousePosition;
	sf::Vector2f mousePositionf;
	int mouseClickCount = 0;
	int drawSource = 0;

	int numRay = 200;
	LightSource source(sf::Vector2f(1400, 800), 200);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
			if (event.type == sf::Event::MouseMoved)
			{
				mousePosition = sf::Mouse::getPosition(window);
				mousePositionf.x = mousePosition.x;
				mousePositionf.y = mousePosition.y;
				source.move(mousePositionf);
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				mousePosition = sf::Mouse::getPosition(window);

				mouseClickCount += 1;
				if (mouseClickCount == 3)
					mouseClickCount = 1;

				if (mouseClickCount == 1)
				{
					tempStartingPoint.x = mousePosition.x;
					tempStartingPoint.y = mousePosition.y;
				}
				else
				{
					tempEndingPoint.x = mousePosition.x;
					tempEndingPoint.y = mousePosition.y;

					Wall wall(tempStartingPoint, tempEndingPoint);
					wallVector.push_back(wall);
				}

			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C)
			{
				wallVector.clear();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				drawSource += 1;
				if(drawSource == 3)
					drawSource = 0;
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
			{
				numRay += 10;
				source.setNumRay(numRay);
				source.move(mousePositionf);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
			{
				numRay -= 10;
				source.setNumRay(numRay);
				source.move(mousePositionf);
			}


		   
		}
		
		//clear and set background color
		window.clear(sf::Color::Black);
		//draw results
		
		source.checkWalls(wallVector);
		if (drawSource == 0)
			source.drawAll(window);
		else if (drawSource == 1)
			source.drawCollisions(window);
		
		for (int i = 0; i < wallVector.size(); i++)
		{
			wallVector[i].draw(window);
		}
		//display final results 
		window.display();
	}
	return 0;
}