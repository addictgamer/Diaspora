/* Copyright Ciprian Ilies */

#pragma once

#include "../../../../../internal_header.hpp"
#include <vector>
#include <iostream>

namespace ws
{

class Dimension;
class Galaxy;

//NOTE: This only exists for the purposes of pseudo-simulation.
//Its biggest use is in world generation.
class Cluster
{
public:
	//NOTE: It's either one of these two, not both.
	Dimension *parent_dimension; //Parent dimension.
	Cluster *parent_cluster; //Parent cluster.

	//Its contained.
	//Can be other clusters and/or galaxies.
	std::vector<Cluster *> clusters;
	std::vector<Galaxy *> galaxies;

	Cluster();
	~Cluster();

	//Generate a new cluster.
	//Returns false on error, true on success.
	//parent_d and parent_c are the cluster's parents (_d = dimension, _c = cluster).
	//Use only one of the two paramaters.
	//Also acts as an initializer.
	bool genNew(Dimension *parent_d, Cluster *parent_c, std::vector<std::string> parameters);
};

} //namespace ws
