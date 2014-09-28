/* Copyright Ciprian Ilies */

#pragma once

#include "../../../../../../../../../../internal_header.hpp"

namespace ws
{

class Space;
class Sector;

/*
	TODO: Change regions to match this picture:

	100 spaces in the region.

	So...

	100x100x100 child spaces.

	So...

	Space *spaces[100][100][100]. Sort of like what's going on in space::genNeighbors().
*/

static const int REGION_SIZE = 10; //TODO: Change to 100 as specified above.

//NOTE: This is used soley for pseudo-simulation purposes.
class Region
{
public:
	Sector *parent_sector; //Its parent sector.
	Sector *parent_celestial_body; //Its parent celestial body.

	Region *left, *right, *up, *down, *above, *below; //Its neighboring regions.

	Space *space; //The space that compromises it.

	Region();
	~Region();

	//Generates the neighbors of this region.
	//NOTE: Assumes that none of its neighbors already exist.
	//NOTE: It only allocates empty space.
	//NOTE: It assumes that this is the top left corner of the sector.
	//void genNeighbors(); //NOTE: Deprecated.

	//Generate this region.
	//Or rather, setup all the empty space.
	void gen();

	//const int SIZE = 100; //All regions contain 10 'tiles' (which are actually the top heirarchy of space. The 'contents' of the tile is/are the children of that space).
};

} //namespace ws
