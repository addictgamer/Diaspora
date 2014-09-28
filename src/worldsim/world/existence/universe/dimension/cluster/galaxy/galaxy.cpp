/* Copyright Ciprian Ilies */

#include "galaxy.hpp"
#include "../cluster.hpp"
#include "solar_system/solar_system.hpp"

#include <iostream>

namespace ws
{

Galaxy::Galaxy()
{
	parent_cluster = nullptr;
}

Galaxy::~Galaxy()
{
	parent_cluster = nullptr; //Reset its parent.

	//Go through and delete all the solar systems.
	while (solar_systems.size() > 0)
	{
		solar_systems[0]->parent_galaxy = nullptr; //Reset its parent.

		//Delete and reset.
		delete solar_systems[0];
		solar_systems[0] = nullptr;

		solar_systems.erase(solar_systems.begin()); //Remove from vector.
	}
}

bool Galaxy::genNew(Cluster *parent, std::vector<std::string> parameters) //Generate the parent.
{
	parent_cluster = parent; //Assign the parent.

	SolarSystem *solarsystem = new SolarSystem; //Allocate memory for a solar system.

	if(!solarsystem->genNew(this, parameters)) //Generate it, with error checking.
	{
		std::cout << "Error: Failed to generate galaxy; Failed to generate solarsystem.\n";
		delete solarsystem; //Cleanup.
		return false; //Abort.
	}

	solar_systems.push_back(solarsystem); //Save it.

	return true; //Success.
}

} //namespace ws
