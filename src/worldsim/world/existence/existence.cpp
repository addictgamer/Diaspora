/* Copyright Ciprian Ilies */

#include "existence.hpp"
#include "universe/universe.hpp"

#include <iostream>

namespace ws
{

Existence::Existence()
{
}

Existence::~Existence()
{
	while(universes.size() > 0) //Loop through all the universes and delete them.
	{
		//Reset and delete.
		universes[0]->parent_existence = nullptr;
		delete universes[0];

		universes.erase(universes.begin()); //Remove from the vector.
	}
}

bool Existence::genNew(std::vector<std::string> parameters)
{
	Universe *universe = new Universe; //Allocate memory for a new universe.

	//Generate new universe.
	//TODO: Make it determine what parameters to pass to the universe. And thus check what to keep for itself to determine things like how many universes it should generate.
	if(!universe->genNew(*this, parameters)) //With error checking.
	{
		std::cout << "Error: Failed to gen new universe. Aborting Existence::genNew()\n";
		delete universe; //Cleanup.
		return false; //Error!
	}

	universes.push_back(universe); //Save in universe vector.

	return true; //Success.
}

} //namespace ws
