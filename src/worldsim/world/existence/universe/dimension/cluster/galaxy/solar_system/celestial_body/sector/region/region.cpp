/* Copyright Ciprian Ilies */

#include "region.hpp"

#include "../sector.hpp"
#include "../../../../../../../../../space/space.hpp"

#include <iostream>

namespace ws
{

Region::Region()
{
	parent_sector = nullptr;
	parent_celestial_body = nullptr;

	left = nullptr;
	right = nullptr;
	up = nullptr;
	down = nullptr;
	above = nullptr;
	below = nullptr;

	space = nullptr;
}

Region::~Region()
{
	parent_sector = nullptr; //Reset parent.
	parent_celestial_body = nullptr;

	//Now go through all of its neighbors and delete them.
	//TODO: If segfaults occur, store the neighbor first in a temp pointer, nullify the original, and then use delete on the temp pointer.
	//This is to avoid the deletion wrapping around and trying to delete nonexistant tiles.

	if (left != nullptr)
	{
		left->right = nullptr; //Reset this, so it doesn't delete this.

		//Delete and reset.
		delete left;
		left = nullptr;
	}

	if (right != nullptr)
	{
		right->left = nullptr; //Reset this, so it doesn't delete this.

		//Delete and reset.
		delete right;
		right = nullptr;
	}

	if (up != nullptr)
	{
		up->down = nullptr; //Reset this, so it doesn't delete this.

		//Delete and reset.
		delete up;
		up = nullptr;
	}

	if (down != nullptr)
	{
		down->up = nullptr; //Reset this, so that it doesn't delete this.

		//Delete and reset.
		delete down;
		down = nullptr;
	}

	if (above != nullptr)
	{
		above->below = nullptr; //Reset this, so that it doesn't delete this.

		//Delete and reset.
		delete above;
		above = nullptr;
	}

	if (below != nullptr)
	{
		below->above = nullptr; //Reset this, so that it doesn't delete this.

		//Delete and reset.
		delete below;
		below = nullptr;
	}

	//NOTE: Do NOTE delete space (for now). As all space currently used (unless somebody is messing around with the code and doing bad stuff) is part of the dimension and is deleted when the dimension's space is deleted.
	/*if (space) //If space exists.
	{
		space->parent_region = nullptr; //Reset this.

		//Delete and reset space.
		delete space;
		space = nullptr;
	}*/
}

void Region::gen()
{
	//std::cout << "Getting in Region::gen()\n";

	if (space) //Check if space already exists.
	{
		std::cout << "Warning: Space already exists for Region in Region::gen()\n";
		return; //Abort.
	}

	space = new Space; //Allocate the space.

	space->genNeighbors(); //Generate the space's neighbors. //TODO: Is this really neccessary? I don't think it is.
}

} //namespace ws
