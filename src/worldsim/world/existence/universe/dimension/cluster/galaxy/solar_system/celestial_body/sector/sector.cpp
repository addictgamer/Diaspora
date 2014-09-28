/* Copyright Cirian Ilies */

#include "sector.hpp"
#include "../celestial_body.hpp"
#include "region/region.hpp"

namespace ws
{

Sector::Sector()
{
	parent_celestial_body = nullptr;

	left = nullptr;
	right = nullptr;
	up = nullptr;
	down = nullptr;
	above = nullptr;
	below = nullptr;

	regions = nullptr;
}

Sector::~Sector()
{
	parent_celestial_body = nullptr; //Reset parent.

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

	if (regions != nullptr)
	{
		regions->parent_sector = nullptr; //Let it know not that its parent exists.

		//Delete and reset.
		delete regions;
		regions = nullptr;
	}
} //Sector::~Sector()



} //namespace ws
