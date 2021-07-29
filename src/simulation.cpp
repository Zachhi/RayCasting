#include "simulation.h"

Simulation::Simulation() : window(sf::VideoMode(2800, 1600), "RayCasting", sf::Style::Fullscreen), source(sf::Vector2f(1400, 800), 200) {}

void Simulation::runSimulation() 
{
	while (window.isOpen())
	{
		//check for input and update accordingly
		checkInput();

		//clear and set background color
		window.clear(sf::Color::Black);

		//draw updated results after every loop
		drawObjects();

		//display final results 
		window.display();
	}
}

void Simulation::checkInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) //close program if x at top right is clicked
			window.close();

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) //close program with escape
			window.close();

		if (event.type == sf::Event::MouseMoved) //every time mouse is moved, update the light source position
		{
			mousePosition = sf::Mouse::getPosition(window);
			mousePositionf.x = mousePosition.x;
			mousePositionf.y = mousePosition.y;
			source.move(mousePositionf);
		}

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) //if left mouse click, draw wall between two points clicked
		{
			mousePosition = sf::Mouse::getPosition(window);

			mouseClickCount += 1;
			if (mouseClickCount == 3)
				mouseClickCount = 1;

			if (mouseClickCount == 1) //if first click, store starting points
			{
				tempStartingPoint.x = mousePosition.x;
				tempStartingPoint.y = mousePosition.y;
			}
			else //if second click, store ending points and make the wall
			{
				tempEndingPoint.x = mousePosition.x;
				tempEndingPoint.y = mousePosition.y;

				Wall wall(tempStartingPoint, tempEndingPoint);
				wallVector.push_back(wall);
			}

		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C) //clear walls with c
		{
			wallVector.clear();
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) //change source with space. either show all light rays, show only the ones touching walls, or show none
		{
			drawSource += 1;
			if (drawSource == 3)
				drawSource = 0;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) //increase amount of light rays with up arrow
		{
			numRay += 10;
			source.setNumRay(numRay);
			source.move(mousePositionf);
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) //decrease amount of light rays with down arrow
		{
			numRay -= 10;
			source.setNumRay(numRay);
			source.move(mousePositionf);
		}



	}
}

void Simulation::drawObjects()
{
	source.checkWalls(wallVector); //update the light rays from source according to the walls in wall vector
	if (drawSource == 0) //now draw depdning on "drawSource" value
		source.drawAll(window);
	else if (drawSource == 1)
		source.drawCollisions(window);

	for (int i = 0; i < wallVector.size(); i++) //draw the walls
	{
		wallVector[i].draw(window);
	}
}