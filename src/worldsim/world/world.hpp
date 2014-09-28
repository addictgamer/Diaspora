/* Copyright Ciprian Ilies */

#pragma once

#include "../internal_header.hpp"
#include <vector>
#include <string>

//Worldsim namespace.
namespace ws
{

class Existence;
class Entity;

class World
{
public:
	//The existence.
	Existence *existence; //TODO: shared_ptr or something to ensure that everything pointing to this upon its deletion is made aware of its deletion. Maybe.

	//mdata::linked_list<Entity *> entities; //TODO: Give the data module a linked list template.
	//For now, we'll use a vector of entities.
	std::vector<Entity *> entities;

	World();
	~World();

	//Generates the world.
	//Output is obviously stored in existence.
	//Returns false on error, true on success.
	bool gen();

	//This function is used to set up the world for playing.
	void embark();

	//TODO: This may or may not be needed.
	void render();

	//Adds something to gen_params.
	void addGenParam(std::string input);

private:
	//Parameters to generate the world with.
	//Used in the gen() function.
	std::string gen_params;
};

} //namespace ws
