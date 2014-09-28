/* Copyright Ciprian Ilies */

#pragma once

#include "../../../../../../../internal_header.hpp"
#include <vector>
#include <string>

namespace ws
{

class Galaxy;
class CelestialBody;

static const int size_small_max = 5; //Max size for a small celestial object. //NOTE: Should be 100. Reduced to 50 for testing.
static const int size_small_min = 1; //Min size for a small celestial object.

//NOTE: This exists solely for the purpose of pseudo-simulation.
class SolarSystem
{
public:
	Galaxy *parent_galaxy; //Its parent galaxy.

	std::vector<CelestialBody *> celestial_bodies; //List of all celestial bodies.

	SolarSystem();
	~SolarSystem();

	//Generate a new Solar System.
	//Returns false on error, true on success.
	//parent is the solar system's parent galaxy.
	//Also acts as an initializer.
	bool genNew(Galaxy *parent, std::vector<std::string> parameters);
};

} //namespace ws.
