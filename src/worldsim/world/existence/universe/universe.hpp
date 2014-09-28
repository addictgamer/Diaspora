/* Copyright Ciprian Ilies */

#pragma once

#include "../../../internal_header.hpp"

#include <string>
#include <vector>

namespace ws
{

class Existence;
class Dimension;

class Universe
{
public:
	Existence *parent_existence; //The Universe's parent existence.

	//The dimensions.
	//A linked list.
	Dimension *dimensions;

	Universe();
	~Universe();

	//Generate a new dimension.
	//Returns false on error, true on success.
	//Parent is the universe's parent existence.
	//Also acts as an initializer.
	bool genNew(Existence &parent, std::vector<std::string> parameters);
};

} //namespace ws
