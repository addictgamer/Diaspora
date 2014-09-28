/* Copyright Ciprian Ilies */

#include "celestial_body.hpp"

#include "sector/sector.hpp"
#include "sector/region/region.hpp"
#include "../solar_system.hpp"
#include "../../galaxy.hpp"
#include "../../../cluster.hpp"
#include "../../../../dimension.hpp"

#include "../../../../../../../space/space.hpp"

#include "../../../../../../../../physics/molecule.hpp"

//#include "../../../../../../../../../engine/graphic/3d/3d.hpp"

#include <iostream>

namespace ws
{

CelestialBody::CelestialBody()
{
	parent_solar_system = nullptr;
	//sectors = nullptr;
	regions = nullptr;
}

CelestialBody::~CelestialBody()
{
	parent_solar_system = nullptr; //Reset parent.

	/*if (sectors != nullptr)
	{
		sectors->parent_celestial_body = nullptr; //Reset parent.

		//Delete and reset.
		delete sectors;
		sectors = nullptr;
	}*/

	if (regions != nullptr)
	{
		regions->parent_celestial_body = nullptr; //Reset parent.

		//Delete and reset.
		delete regions;
		regions = nullptr;
	}
}

bool CelestialBody::genNew(SolarSystem *parent, std::vector<std::string> parameters, long size) //Generate the celestial body.
{
	//std::cout << "Getting in CelestialBody::genNew()\n";

	parent_solar_system = parent; //Set parent.

	//Hmm...Sectors, or skip that and go to regions, or go directly to space?

	//regions = new Region; //Allocate the regions.

	//regions->gen(); //Generate the region.

	//std::cout << "\nTest1\n";

	//if (regions->space != nullptr) //No space is wanted right now.
	//{
	//	delete regions->space; //Delete the space of the region.
	//}

	//std::cout << "Test2\n";

	//Save a pointer to the highest level space so that I don't have to type out its path.
	Space *toplevel_space = parent_solar_system->parent_galaxy->parent_cluster->parent_dimension->space;

	Space *current = toplevel_space; //The current space.

	/*//Recursively generate space down to this level.
	//22 because the dimension's space is on the supercluster level.
	//Actually, 21. 22 is the 1x1x1m scale. 22 because we want regions to have more space.
	for (int i = 0; i < 21; ++i)
	{
		current->space = new Space; //Allocate memory for the child of that space.
		current = current->space; //Mooooving on up (Down).
	}*/
	current->subdivide(0, 0, (SPACE_SIZE - 1), 21); //Subdivide the space...

	//Loop to the lowest space.
	while(current->getChild(0, 0, (SPACE_SIZE - 1))) //Loop down while has children space.
	{
		current = current->getChild(0, 0, (SPACE_SIZE - 1)); //Move to it!
	}


	//regions->space = current; //Point this space to the current space. (Oh dear. Things might get itchy.)

	//current->genNeighbors(); //Generate the space's neighbors. //TODO: Is this really needed? I don't think so.

	//current->genChildren(); //Generate all the spaces located on the 22nd level down from 10^22 meters cubed.

	//current->left()->genChildren(); //Generate the spaces to the down (as in, south, not above or below) of this group of spaces. So that we can have more room to play around in.

	{

		//TODO: Generate the thing. For now, it's a simple cube. Booooring.

		//Ok. So here's how this is going to be done.
		//Take the spot in the middle of the cubular region of space...

		int startx = (SPACE_SIZE / 2) - (size / 2);
		int starty = (SPACE_SIZE / 2) - (size / 2);
		int startz = (SPACE_SIZE / 2) + (size / 2); //Let's go top -> down.

		//TODO: Maybe have it determine an acceptible starting range and randomly decide where to gen?

		std::cout << "Starting coordinates: [" << startx << "][" << starty << "][" << startz << "]\n";

		//Molecule *molecule; //The molecule the asteroid will be made up of.
		//Atom *atom; //The atom the asteroid will be made up of.

		//For now, I'm just going to copy some default atom into the asteroid. Say, iron.

		if (!current)
		{
			std::cout << "Error: current does not exist.\n";
			throw;
		}

		//First, move to the intial position.
		/*for (int x = 0; x < startx; ++x)
		{
			for (int y = 0; y < starty; ++y)
			{
				for (int z = SPACE_SIZE; z > startz; --z)
				{
					std::cout << "Coordinates [" << x << "][" << y << "][" << z << "]\n";

					if (!current->below)
					{
						std::cout << "Ruh Roh! Something done broke at line " << __LINE__ << " in file " << __FILE__ << ".\n";
						throw; //TODO: Throw a proper exception.
					}
					current = current->below; //Move down through the layers to reach the top layer.
				}

				if (!current->down)
				{
					std::cout << "Ruh Roh! Something done broke at line " << __LINE__ << " in file " << __FILE__ << ".\n";
					throw; //TODO: Throw a proper exception.
				}
				current = current->down; //Move down the flat plane thingy when looking top-down at the world. Or top-down in a 2D SDL game.
			}


			if (!current->right)
			{
				std::cout << "Ruh Roh! Something done broke at line " << __LINE__ << " in file " << __FILE__ << ".\n";
				throw; //TODO: Throw a proper exception.
			}

			current = current->right; //Move to the right until the correct position is reached.
		}*/

		/***********OBSOLETE CODE*************/
		/*//Move to the starting space.
		for (int x = 0; x < startx; ++x)
		{
			if (!current->right)
			{
				std::cout << "Ruh Roh! Something done broke at line " << __LINE__ << " in file " << __FILE__ << ".\n";
				throw;
			}

			current = current->right;
		}
		for (int y = 0; y < starty; ++y)
		{
			if (!current->down)
			{
				std::cout << "Ruh Roh! Something done broke at line " << __LINE__ << " in file " << __FILE__ << ".\n";
				throw;
			}

			current = current->down;
		}
		for (int z = SPACE_SIZE; z > startz; --z)
		{
			if (!current->below)
			{
				std::cout << "Ruh Roh! Something done broke at line " << __LINE__ << " in file " << __FILE__ << ".\n";
				throw;
			}

			current = current->below;
		}

		std::cout << "Test.\n";*/
		/***********END OBSOLETE CODE*************/


		/***********OBSOLETE CODE*************/
		/*Space *tower = current; //Pointer to the start of the tower (z axis).
		Space *column = current; //Pointer to the start of the column.

		//Now the generating starts.
		for (int x = startx; x < startx + size; ++x)
		{
			for (int y = starty; y < starty + size; ++y)
			{
				for (int z = startz; z > startz - size; --z)
				{
					std::cout << "Setting space at coordinates: [" << x << "][" << y << "][" << z << "] to be made of (an, currently) iron molecules.\n";
					current->setMolecule(*MOLECULE_IRON); //Set the molecule.
					//current->molecules = new Molecule;
					//current->molecules->set(*MOLECULE_IRON);
					current->model->translate(x, y, z); //Set the model into position.

					//Move on.
					if (!current->below) //TODO: Make this check be included in some kind of space::moveTo thing. Or something. Maybe if(!space->tmove(space->below)) throw error; ?
					{
						std::cout << "Ruh Roh! Something done broke at line " << __LINE__ << " in file " << __FILE__ << ".\n";
						throw; //TODO: Throw a proper exception.
					}
					current = current->below; //Move down through the layers to reach the top layer.
				}

				current = tower; //Move to the top of the tower.
				//And then move down, if such a place exists.
				if (!current->down) //TODO: Make this check be included in some kind of space::moveTo thing. Or something. Maybe if(!space->tmove(space->down)) throw error; ?
				{
					std::cout << "Ruh Roh! Something done broke at line " << __LINE__ << " in file " << __FILE__ << ".\n";
					throw; //TODO: Throw a proper exception.
				}
				current = current->down; //Moving along.
			}

			current = column; //Move to start of the column.
			//And then move right, if such a place exists.
			if (!current->right) //TODO: Make this check be included in some kind of space::moveTo thing. Or something. Maybe if(!space->tmove(space->right)) throw error; ?
			{
				std::cout << "Ruh Roh! Something done broke at line " << __LINE__ << " in file " << __FILE__ << ".\n";
				throw; //TODO: Throw a proper exception.
			}
			current = current->right; //Moving along.
		}*/
		/***********END OBSOLETE CODE*************/

		for (int x = startx; x < startx + size; ++x)
		{
			for (int y = starty; y < starty + size; ++y)
			{
				for (int z = startz; z > startz - size; --z)
				{
					std::cout << "Setting space at coordinates: [" << x << "][" << y << "][" << z << "] to be made of (an, currently) iron molecules.\n";
					current->getChild(x, y, z)->setMolecule(*MOLECULE_IRON); //Set the molecule.
					//current->molecules = new Molecule;
					//current->molecules->set(*MOLECULE_IRON);
					//current->space[x][y][z]->x = x;
					//current->space[x][y][z]->y = y;
					//current->space[x][y][z]->z = z;
				}
			}
		}
	}

	return true; //Success.
}

} //namespace ws
