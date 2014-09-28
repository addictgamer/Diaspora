/* Copyright Ciprian Ilies */

/*
The purpose of this file is to test the worldsim code, frankly.
It generates a world.
*/

#include "internal_header.hpp"

//Worldsim dependencies.
#include "world/world.hpp"

using namespace ws;

bool genNew(World *world)
{
	//Check if the world exists.
	if(world != nullptr)
	{
		//Delete and reset it.
		delete world;
		world = nullptr;
	}

	world = new World; //Allocate memory for the world.

	//Here we specify parameters to generate the world with.
	world->addGenParam("<celestial_body_instance>[type=asteroid][size=small]"); //Tell it to generate a small asteroid.
	world->gen(); //Generate a new world.

	//Now let's create an entity.
	//This entity will need to point to...a floating eyeball for now (or something). Anything, so long as it works.
	//BUT HOW DO I TELL IF IT WORKS? BLARG.
	//Ok, ok. How about I just make a floating eyeball from the start. Or, no. How about a sheet. A floating sheet. Light hits the sheet and the entity's hooks tell the graphics blarg "HAY DRAW THIS AND THIS AND THIS" and magic and stuff and I just hope it works.
	//So. I'll also need to simulate light. BJKSJDFLIJSDF how does that?

	return true; //Success.
}

bool genFlatworld(World *&world)
{
	//Check if the world exists.
	if(world != nullptr)
	{
		//Delete and reset it.
		delete world;
		world = nullptr;
	}

	world = new World; //Allocate memory for the world.

	//Here we specify parameters to generate the world with.
	world->addGenParam("<flatworld>"); //Tell it to generate a small asteroid.
	return world->gen(); //Generate a new world. Return the result (failure or success).
}
