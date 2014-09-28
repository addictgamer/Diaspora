/* Copyright Ciprian Ilies */

#include "solar_system.hpp"
#include "../galaxy.hpp"
#include "celestial_body/celestial_body.hpp"

#include <iostream>

#include <GEngine/GEngine.hpp>

using namespace GEngine;

namespace ws
{

SolarSystem::SolarSystem()
{
	parent_galaxy = nullptr;
}

SolarSystem::~SolarSystem()
{
	parent_galaxy = nullptr;

 	while (celestial_bodies.size() > 0) //Go through all the celestial bodies.
	{
		celestial_bodies[0]->parent_solar_system = nullptr; //Reset the parent.

		//Delete and reset.
		delete celestial_bodies[0];
		celestial_bodies[0] = nullptr;

		celestial_bodies.erase(celestial_bodies.begin()); //Remove from vector.
	}
}

bool SolarSystem::genNew(Galaxy *parent, std::vector<std::string> parameters) //Generate the solar system.
{
	parent_galaxy = parent;

	//TODO: Read parameters and generate solar system.

	//TODO: For now I'll use this. Later, switch to the class thing which lets me retrieve parameters.

	//Check if there even are any parameters.
	if (parameters.size() == 0)
	{
		std::cout << "Nothing to do in solarsystem creation.!\n";
		return false; //We might as well error it.
	}

	for (unsigned int i = 0; i < parameters.size(); ++i)
	{
		std::cout << "Parameter: " << parameters[i] <<"\n";
	}

	//You know what, forget it for now.

	//The below could probably best be put in the celestial body's gen object. Whatever.

	std::cout << "\n\nCelestial object will be small.\n";
	std::cout << "Minsize: " << size_small_min << " and maxsize: " << size_small_max << "\n";

	int size = mmisc::mrand::randi(size_small_min, size_small_max);

	std::cout << "Size has randomly been set to: " << size << "\n";

	CelestialBody *object = new CelestialBody; //Allocate a new celestial body.

	std::vector<std::string> params;
	params.push_back(""); //Don't give it any parameters.

	if (!object->genNew(this, params, size)) //Generate a new object. With error checking.
	{
		std::cout << "Error: Failed to generate new solar system: Failed to generate new celestial body.\n";
		delete object; //Clean up.
		return false; //Abort.
	}

	celestial_bodies.push_back(object);

	return true; //Success.
}

} //namespace ws
