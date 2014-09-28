/* Copyright Ciprian Ilies */

#pragma once

#include "../../../../../../../../../internal_header.hpp"

namespace ws
{

class CelestialBody;
class Region;

//NOTE: Only used for pseudo-simulations.
class Sector
{
public:
	CelestialBody *parent_celestial_body; //Its parent.

	Sector *left, *right, *up, *down, *above, *below; //Its neighbors.

	Region *regions; //Its regions.

	Sector();
	~Sector();

	void generate(); //Generate the sector.

	//10x10x10 children. So 1000 children regions.
	static const int sectorsize = 10;
};

} //namespace ws
