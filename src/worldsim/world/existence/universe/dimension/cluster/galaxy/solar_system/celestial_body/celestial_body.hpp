/* Copyright Ciprian Ilies */

#pragma once

#include "../../../../../../../../internal_header.hpp"

#include <vector>
#include <string>

namespace ws
{

class SolarSystem;
class Sector;
class Region;

//Note: This exists solely for pseudo-simulation purposes.
class CelestialBody
{
public:
	SolarSystem *parent_solar_system; //Its parent solar system.

	//Sector *sectors; //List of all the sectors.
	Region *regions; //List of all regions.

	CelestialBody();
	~CelestialBody();

	//Generate a new Celestial Body.
	//Returns false on error, true on success.
	//parent is the celestial body's parent solar system.
	//Also acts as an initializer.
	bool genNew(SolarSystem *parent, std::vector<std::string> parameters, long size);
};

} //namespace ws
