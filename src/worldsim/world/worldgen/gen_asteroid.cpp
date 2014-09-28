/* Copyright Ciprian Ilies */

#include "world_gen_functions.hpp"

//For the complete definition of world.
#include "../world.hpp"

//For the complete definition of existence.
#include "../existence/existence.hpp"

#include <iostream>

namespace ws
{

//Generate an asteroid.
bool genAsteroid(World &world, std::vector<std::string> parameters)
{
	//TODO: Generate an asteroid.

	std::cout << "Generating asteroid.\n\n";

	world.existence = new Existence; //Allocate memory for it.

	/*Generate new existence.
	The parameters are recursively passed down until a level where, say, existence -> universe -> galaxy.
	At the galaxy level, 3 galaxies are specified for creation.
	Well, then it splits the parameters up. Each galaxy gets the pertinent portion of the parameter.
	Further one, one of the galaxies has three solar systems, and five planets in one of those systems.
	The portion of paremter passed to the galaxy is split up and the resulting splits are passed to wherever they are needed.
	*/
	if (!world.existence->genNew(parameters)) //With error checking.
	{
		std::cout << "Error: Failed to generate existence. Aborting genAsteroid()\n";
		return false;
	}

	return true;
}

} //namespace ws
