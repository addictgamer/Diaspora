/* Copyright Ciprian Ilies */

#pragma once

#include "../../../../internal_header.hpp"

#include <vector>
#include <string>

namespace ws
{

class Universe;
class Cluster;
class Space;

class Dimension
{
public:
	Dimension *next, *previous; //The pointers to the next and previous dimension.

	Universe *parent_universe; //Its parent universe.

	//The clusters.
	//A RCMS.
	//Hmm...Actually, this is a bit tricky...
	//I know how it'll work!
	Space *space;
	//There, the dimension is defined as a recursive cube map of space. Each space contains...stuff. Man, this is hard. I need to organize the universe into clusters, which are further organized into galaxies. Which are further organized into solar systems and celestial bodies. I got it! That stuff is only for DNA and generation and stuff anyway. They don't matter here.

	std::vector<Cluster *> clusters; //Children clusters.

	Dimension();
	~Dimension();

	//Generates a new dimension.
	//Returns false on error, true on success.
	//Parent is the dimension's parent universe.
	//Also acts as an initializer.
	bool genNew(Universe &parent, std::vector<std::string> parameters);
};

} //namespace ws
