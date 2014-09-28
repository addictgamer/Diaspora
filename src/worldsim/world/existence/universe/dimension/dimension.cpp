/* Copyright Ciprian Ilies */

#include "dimension.hpp"

#include "../universe.hpp"
#include "../../../space/space.hpp"
#include "cluster/cluster.hpp"

#include <iostream>

namespace ws
{

Dimension::Dimension()
{
	parent_universe = nullptr;

	next = nullptr;
	previous = nullptr;

	space = nullptr;
}

Dimension::~Dimension()
{
	parent_universe = nullptr;

	if (next != nullptr) //If next neighbor exists.
	{
		//Delete and reset.
		delete next;
		next = nullptr;
	}

	if (previous != nullptr) //If previous neighbor exists.
	{
		//Delete and reset.
		delete previous;
		previous = nullptr;
	}

	if (space != nullptr) //If space exists.
	{
		//Delete and reset.
		deleteSpace(space);
		space = nullptr;
	}

	//Go through all the clusters and delete them.
	while (clusters.size() > 0)
	{
		//Delete. Reset. Remove from vector.
		clusters[0]->parent_dimension = nullptr;
		delete clusters[0];
		clusters[0] = nullptr;
		clusters.erase(clusters.begin());
	}
}

//Generate a new dimension.
bool Dimension::genNew(Universe &parent, std::vector<std::string> parameters)
{
	parent_universe = &parent; //Asign the parent.

	space = new Space; //Allocate memory for the space.

	//TODO: Decide how to do this...What level is the space on? What dimensions?

	/*How about this:
	This has space pointing to the 1x1x1m tile.
	Or no.
	Point it to the supercluster scale.
	Ya.
	Then generate downards.
	No.
	Wait. Ya.
	No.
	Stick with the supercluster scale, ya. Then generate down from 1x10^22meters to 1 meter gradually up till the celestial body generation blarg.
	*/

	//space->genNeighbors(); //Generate its neighbors. //No, don't do that! It'll fill up all the RAM...

	//Check if there even are any parameters.
	if (parameters.size() == 0)
	{
		std::cout << "No parameters specified. Generating flat world.\n";

		//TODO: Generate flat world.

		//TODO: The rest of the world will be generated in the level editor.
		//So everything starts off as a void, basically.
	}
	else
	{
		for (unsigned int i = 0; i < parameters.size(); ++i)
		{
			std::cout << "Parameter: " << parameters[i] <<"\n";
			//TODO: Look through parameters and go on from there.
		}
		return false; //TODO: This is temp.

		Cluster *cluster = new Cluster; //A new cluster.

		if(!cluster->genNew(this, nullptr, parameters)) //Generate the cluster, with error checking.
		{
			std::cout << "Error: Failed to generate dimension; Failed to generate cluster.\n";
			delete cluster; //Cleanup.
			return false; //Error, abort!
		}

		clusters.push_back(cluster); //Save this cluster.
	}

	return true; //Success.
}

} //namespace ws
