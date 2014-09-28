/* Copyright Ciprian Ilies */

#include <iostream>

//For the complete definition of world.
#include "../world.hpp"

//For the complete definition of existence.
#include "../existence/existence.hpp"

#include "world_gen_functions.hpp"

namespace ws
{

bool genFlatworld(World &world, std::vector<std::string> parameters)
{
	//TODO: Generate a flat world.

	std::cout << "Generating flat world.\n\n";

	world.existence = new Existence; //Allocate memory for it.

	/*
	 * Generate new existence.
	 * It's going to be an infinitely flat plane. Well, not necessarily flat. There will be mountains and what have you.
	 */
	if (!world.existence->genNew(parameters)) //With error checking.
	{
		std::cout << "Error: Failed to generate existence. Aborting genFlatworld()\n";
		return false;
	}
	return true; //Success.
}

} //namespace ws
