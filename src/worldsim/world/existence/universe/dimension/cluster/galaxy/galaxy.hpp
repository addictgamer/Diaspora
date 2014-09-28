/* Copyright Ciprian Ilies */

#pragma once

#include "../../../../../../internal_header.hpp"
#include <vector>
#include <string>

namespace ws
{

class Cluster;
class SolarSystem;

//NOTE: This exists only for the purposes of pseudo-simulation.
class Galaxy
{
public:
	//Its parent cluster.
	//Can be an 'empty' cluster (that is, a cluster with only this galaxy in it) to signify a rogue galaxy.
	Cluster *parent_cluster;

	std::vector<SolarSystem *> solar_systems; //The solar systems contained therein.

	Galaxy();
	~Galaxy();

	//Generate a new Galaxy.
	//Returns false on error, true on success.
	//parent is the galaxy's parent cluster.
	//Use only one of the two paramaters.
	//Also acts as an initializer.
	bool genNew(Cluster *parent, std::vector<std::string> parameters);
};

} //namespace ws
