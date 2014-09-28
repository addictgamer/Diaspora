/* Copyright Ciprian Ilies */

#include "cluster.hpp"
#include "../dimension.hpp"
#include "galaxy/galaxy.hpp"

namespace ws
{

Cluster::Cluster()
{
	parent_dimension = nullptr;
	parent_cluster = nullptr;
}

Cluster::~Cluster()
{
	//Reset its parents.
	parent_dimension = nullptr;
	parent_cluster = nullptr;

	//Go through all the clusters and delete them.
	while (clusters.size() > 0)
	{
		//Delete and reset.
		delete clusters[0];
		clusters[0] = nullptr;
		//Remove from vector.
		clusters.erase(clusters.begin());
	}

	while (galaxies.size() > 0)
	{
		//Delete and reset.
		delete galaxies[0];
		galaxies[0] = nullptr;

		//Remove from vector.
		galaxies.erase(galaxies.begin());
	}
}

bool Cluster::genNew(Dimension *parent_d, Cluster *parent_c, std::vector<std::string> parameters)
{
	if(!parent_d && !parent_c)
	{
		std::cout << "Error: Failed to generate new cluster; Need a parent.\n";
		return false;
	}

	//Assign parents.
	//Only one of the two parents can be used.
	if (parent_d != nullptr)
	{
		parent_dimension = parent_d;
	}
	else
	{
		parent_cluster = parent_c;
	}

	Galaxy *galaxy = new Galaxy; //Allocate a new galaxy.

	if(!galaxy->genNew(this, parameters)) //Generate the galaxy. With error checking.
	{
		std::cout << "Error: failed to generate cluster: Failed to generate galaxy.\n";
		delete galaxy; //Cleanup.
		return false;
	}

	galaxies.push_back(galaxy); //Save it.

	return true; //Success.
}

} //namespace ws
