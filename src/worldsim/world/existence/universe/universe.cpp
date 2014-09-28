/* Copyright Ciprian Ilies */

#include "universe.hpp"
#include "../existence.hpp"
#include "dimension/dimension.hpp"

#include <iostream>

namespace ws
{

Universe::Universe()
{
	parent_existence = nullptr;
	dimensions = nullptr;
}

Universe::~Universe()
{
	parent_existence = nullptr; //Nullify this.

	if (dimensions != nullptr) //Check if dimensions exist.
	{
		dimensions->parent_universe = nullptr;

		delete dimensions; //Delete dimensions.
		dimensions = nullptr; //Nullify it.
	}
}

bool Universe::genNew(Existence &parent, std::vector<std::string> parameters) //Generate a new universe.
{
	parent_existence = &parent; //Assign the parent existence.

	dimensions = new Dimension; //Allocate memory for the dimension.

	//Generate the dimension, passing the parameters to it.
	//TODO: Make it parse the parameters and determine what to give is for it and what to pass on (and who to pass it on to).
	if (!dimensions->genNew(*this, parameters)) //With error checking.
	{
		std::cout << "Error: Failed to generate dimension! Aborting Universe::genNew()\n";
		return false; //Error.
	}

	return true; //Success!
}

} //namespace ws
