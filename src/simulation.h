#ifndef SIMULATION_H
#define SIMULATION_H
#include "light/lightSource.h"

class Simulation
{
private:
	sf::RenderWindow window; //window object

	std::vector<Wall> wallVector; //vector of all the walls drawn

	sf::Vector2i mousePosition; //will store the mouse position in int form
	sf::Vector2f mousePositionf; //will store the mouse position in float form

	sf::Vector2f tempStartingPoint; //holds starting and ending point of a wall that is being drawn
	sf::Vector2f tempEndingPoint;

	int mouseClickCount = 0; //keeps track of which mouse click we are on, so we know to store and draw a wall on the second click
	int drawSource = 0; //keeps track of what type of source we are drawing. Either all rays, none, or only the ones touching walls

	int numRay = 200; //number of rays we wish to start with
	LightSource source; //the light source

public:
	Simulation();
	void runSimulation(); //run the simulation
	void checkInput(); //check user input
	void drawObjects(); //draw everything

};
#endif //SIMULATION_H