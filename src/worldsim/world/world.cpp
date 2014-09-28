/* Copyright Ciprian Ilies */

#include "world.hpp"

#include "../physics/subatomic_particle.hpp"
#include "../physics/atom.hpp"
#include "../physics/molecule.hpp"

#include <iostream>

//So that it has the complete types of class Entity and class Existence.
#include "entity/entity.hpp"
#include "existence/existence.hpp"

//For all the world generating calls we have to make.
#include "worldgen/world_gen_functions.hpp"

namespace ws
{

World::World()
{
	existence = nullptr;

	gen_params = "";
}

World::~World()
{
	if (existence != nullptr) //Check if the existence exists.
	{
		delete existence; //Delete the existence.
		existence = nullptr;
	}

	while (entities.size() > 0) //Go through all the entities and delete them.
	{
		delete entities[0]; //Delete it.
		entities.erase(entities.begin()); //Remove it from the vector.
	}
}

bool World::gen() //Generate a world.
{
	//Whee, generating.

	//Make sure we have generate parameters.
	if (gen_params == "")
	{
		//We do not.
		std::cout << "Error: No gen parameters provided.";
		return false; //Abort.
	}

	//Set up things we'll need.

	//Set up all the subatomic particles.
	setupParticles();

	if (!setupAtoms()) //Set up atoms, with error checking.
	{
		std::cout << "Error: Failed to set up atoms!\n";
		return false;
	}

	if (!setupMolecules()) //Set up molecules, with error checking.
	{
		std::cout << "Error: Failed to set up molecules!\n";
		return false;
	}

	/*
	TODO: Change these to use an identifier block class, where instead of "string block_identifier", it's "IdentifierBlock block_identifier" or something.
	That class contains member "string blockname", which is the equivalent of the current "string block_identifier".
	It also contains the vector of parameters, which are in themselves classes, with a "name" member, and a "value" member.
	TODO: All that ^ could probably be made a data structure in the config or data engine modules...And then the below functions be incorporated into them to make this file only contain some function calls rather than all this parsing code.
	*/
	//The stuff in the <> at the beginning of the block.
	std::string identifier = "";
	//The parameters (the stuff in the []) are stored here.
	std::vector<std::string> parameters;

	//Go through gen_params and extract the first param.
	std::string temp; //Used for...Taking all the characters gone through so far and blarging them together to figure out what's going on.
	bool done = false; //Loop control.
	unsigned int i = 0; //Index.
	bool recording_identifier = false; //Is it recording stuff?
	bool recording_parameter = false; //Is it recording the actual parameter (the stuff in the [])?
	while (!done)
	{

		bool record = true; //Will it be recording this loop?

		//If the opening character to an identifier has been found.
		if (gen_params[i] == '<')
		{
			//Now determine what to do.
			//Is it recording a parameter (the stuff in the [])?
			if (recording_parameter)
			{
				//It is. Do nothing, as it's just going to record the '<'.
			}
			//Check if it's already recording the identifier.
			else if (recording_identifier)
			{
				//This is bad. Malformed gen_params.
				std::cout << "gen_params: \"\n";
				std::cout << gen_params; //Write out gen_params for the user to see what happened.
				std::cout << "\"\n\n\n\n"; //End blarg formatting.
				return false; //Abort!
			}
			//Ok, everything looks to be good.
			//Now it proceeds to check if it can tell it to start recording the identifier.
			else if (!recording_identifier)
			{
				//Oooh, now it does something.
				//Namely, it starts recording the identifier.
				//And it tells it to not record anything this loop (which would otherwise record a '<'.
				recording_identifier = true; //It is recording.
				record = false; //Do not record anything this loop.
			}
			//This final else should never be reached.
			else
			{
				std::cout << "Error: Reached else that should never be reached on line " << __LINE__ << " in file \"" << __FILE__ << "\"\n";
				return false; //Abort.
			}
		}
		//No? Ok. Check if it's the closing character to an identifier.
		else if (gen_params[i] == '>')
		{
			//Same deal as above. Determine what to do.
			//Recording a parameter?
			if (recording_parameter)
			{
				//Same as above. It doesn't care, it just goes ahead and records it.
			}
			//Check if not recording a parameter and not recording an identifier.
			else if (!recording_identifier)
			{
				//Woah, it's not recording a parameter and not recording an identifier. That's bad!
				//Write out the error (malformed gen_params) and abort.
				std::cout << "\n\n\n\nError: Malformed gen_params.\n";
				std::cout << "gen_params: \"\n";
				std::cout << gen_params; //Write out gen_params for the user to see what happened.
				std::cout << "\"\n\n\n\n"; //End blarg formatting.
				return false; //Abort!
			}
			//Last check. Is it recording an identifier?
			else if (recording_identifier)
			{
				//It is. Good.

				recording_identifier = false; //No longer recording an identifier.
				record = false; //Don't record anything this loop.

				//All that's left is to blarg it into the identifier string.
				identifier = temp; //Blarg it.
				temp = "";
			}
			//This final else should never be reached.
			else
			{
				std::cout << "Error: Reached else that should never be reached on line " << __LINE__ << " in file \"" << __FILE__ << "\"\n";
				return false; //Abandon ship!
			}
		}
		//Mkay. Time for the checks pertaining to the parameter (the []).
		//First, it checks for the opening character.
		else if (gen_params[i] == '[')
		{
			//Same as the first two ifs, except here it looks to see if it's the identifier that's already recording.
			if (recording_identifier)
			{
				//Do nothing. It doesn't care, it's just gonna record it later.
			}
			//Now the validity checking (that is, making sure that gen_params is formatted correctly such that there are no '['s in a parameter.
			else if (recording_parameter)
			{
				//A malformed gen_params, eh? Write out the error and abort.
				std::cout << "\n\n\n\nError: Malformed gen_params.\n";
				std::cout << "gen_params: \"\n";
				std::cout << gen_params; //Write out gen_params for the user to see what happened.
				std::cout << "\"\n\n\n\n"; //End blarg formatting.
				return false; //Abort!
			}
			//Ah, the good old final check. It's the one that tells it to start recording a parameter.
			else if (!recording_parameter)
			{
				//All's well. Start recording a parameter.

				recording_parameter = true; //It is now recording a parameter.
				record = false; //Do not record anything this loop (since otherwise it'd record the '['.
			}
			//This final else should never be reached.
			else
			{
				std::cout << "Error: Reached else that should never be reached on line " << __LINE__ << " in file \"" << __FILE__ << "\"\n";
				return false; //Abort.
			}
		}
		//Last check of this block. I sit a ']', marking the end of a parameter?
		else if (gen_params[i] == ']')
		{
			//The usual procedure. First check if it's actually recording the identifier.
			if (recording_identifier)
			{
				//It is. Do nothing! Since it wants to record the ']'
			}
			//Now is the malformity check.
			else if (!recording_parameter)
			{
				//Ruh Roh! recording_parameter should be equal to true!
				//Write out the error and abort.
				std::cout << "\n\n\n\nError: Malformed gen_params.\n";
				std::cout << "gen_params: \"\n";
				std::cout << gen_params; //Write out gen_params for the user to see what happened.
				std::cout << "\"\n\n\n\n"; //End blarg formatting.
				return false; //Abort.
			}
			//And finally, the check that it should start recording.
			else if (recording_parameter)
			{
				//Good, everything's nice and calm and there are no blaring errors or mistakes.

				//Tell it to stop recording.
				recording_parameter = false; //No longer recording parameter.
				record = false; //No longer recording.

				parameters.push_back (temp); //Save the parameter.
				temp = ""; //Reset temp.
			}
			//This final else should never be reached.
			else
			{
				std::cout << "Error: Reached else that should never be reached on line " << __LINE__ << " in file \"" << __FILE__ << "\"\n";
				return false; //Abort.
			}
		}

		if (record) //If it's supposed to be recording.
		{
			//Check if it is recording and then record this entry.
			if (recording_identifier || recording_parameter)
			{
				temp += gen_params[i]; //Save the current index to temp (in other words, record it).
			}
		}


		//And now the end of loop stuff.
		++i; //Increment.

		//Make sure not overun or reached end of string.
		if (i >= gen_params.size())
		{
			done = true; //Done!

			//Now make sure it finished recording everything proper.
			if (recording_identifier) //First the identifier.
			{
				//Uh oh, still recording identifier.
				std::cout << "Error: Reached end of gen_params but still recording identifier!\n";
				return false; //Abort!
			}
			else if (recording_parameter) //Now the parameter.
			{
				//Uh oh, still recording parameter.
				std::cout << "Error: Reached end of gen_params but still recording parameter!\n";
				return false; //Abort!
			}
		}
	}

	//Now take all that blarg it just did and reap the fruits of the labor, and generate what it's supposed to generate.
	//First check if it's supposed to be generating a celestial body.
	if (identifier == "celestial_body_instance")
	{
		//It is. Call the gen asteroid function and pass the other parameters to it.
		if (!genAsteroid(*this, parameters)) //With error checking.
		{
			std::cout << "Error: genAsteroid() returned false.\n";
			return false; //Abort.
		}
	}
	//This should be first, but I'll worry about it later.
	//Check if it should be generating an infinite flat world.
	else if (identifier == "flatworld")
	{
		if (!genFlatworld(*this, parameters)) //Generate the flat world. With error checking.
		{
			std::cout << "Error: genFlatworld() returned false.\n";
			return false; //Abort.
		}
	}	
	else
	{
		//Unknown identifier.
		std::cout << "Error: unknown identifier passed to World::gen()";
		return false; //Failure. Abort.
	}

	return true; //Success.
}

//This function is used to set up the world for playing.
void World::embark()
{
}

void World::render()
{
}

//Adds a parameter to the world generator parameters.
void World::addGenParam(std::string input)
{
	//First, make sure that gen_params ends correctly (for formatting purposes).
	if (gen_params[gen_params.size() - 1] != '\n')
	{
		//Does not end correctly.
		//Format it correctly by adding the needed ending.
		gen_params += "\n"; //Yep, a newline. That's how the parameters are seperated.
	}

	gen_params += input; //Now add the input to the parameter list.

	//Check if the input does not have the newline.
	if (input[input.size() - 1] != '\n')
	{
		//Does not have newline.
		gen_params += "\n"; //Add the newline to gen_params, where it's needed for formatting purposes.
	}
}

} //namespace ws
