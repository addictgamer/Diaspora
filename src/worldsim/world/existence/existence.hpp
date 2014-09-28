/* Copyright Ciprian Ilies */

#pragma once

#include "../../internal_header.hpp"

#include <vector>
#include <string>

namespace ws
{

class Universe;

class Existence
{
public:
	//The universes.
	//They are not stored in the RCMS because universes are not a grid based thing.
	std::vector<Universe *> universes;

	Existence();
	~Existence();

	//Generates a new existence.
	//Returns true on success, false on failure.
	bool genNew(std::vector<std::string> parameters);
};

} //namespace ws
