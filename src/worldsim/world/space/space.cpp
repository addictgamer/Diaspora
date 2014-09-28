/* Copyright Ciprian Ilies */

#include "space.hpp"

#include <iostream>

#include "../../physics/molecule.hpp"

#include "../entity/entity.hpp"

//#include "../../../engine/graphic/3d/3d.hpp"

#include "../../../game/game.hpp"

namespace ws
{

Space::Space()
{
	//First the parent and the children.
	parent_space = nullptr;
	//Set up the space vector.
	space.resize(SPACE_SIZE);
	for (int i = 0; i < SPACE_SIZE; ++i)
	{
		space[i].resize(SPACE_SIZE);

		for (int j = 0; j < SPACE_SIZE; ++j)
		{
			space[i][j].resize(SPACE_SIZE);
		}
	};

	//The second set of children, used in pseudo-simulation.
	dimension = nullptr;
	cluster = nullptr;
	galaxy = nullptr;
	solar_system = nullptr;
	celestial_body = nullptr;
	sector = nullptr;
	region = nullptr;

	parent_region = nullptr;

	//TODO: This might fix it, this might not.
	x = (SPACE_SIZE / 2);
	y = (SPACE_SIZE / 2);
	z = (SPACE_SIZE / 2);

	//The neighbors.
	//left = nullptr;
	//right = nullptr;
	//up = nullptr;
	//down = nullptr;
	//above = nullptr;
	//below = nullptr;

	//Umm. Its composition.
	molecules = nullptr;

	//----------GAME SPECIFIC CODE BELOW----------
	sprite = nullptr;
}

/*Space::Space(Space &_parent_space)
{
	//this = Space(); //TODO: See if this works. I want something like it, to set up an empty space and then let me do additional setup.

	//this->parent_space = _parent_space; //Set this.

	//TODO: MAKE THIS THING WORK.
}*/

Space::~Space()
{
	//Simply nullify this.
	//parent_space = nullptr;
	//Nevermind, better idea:

	if (parent_space) //If the parent space exists...
	{
		//Delete it.

		parent_space->space[x][y][z] = nullptr; //Hide this child from the parent.
		delete parent_space; //Delete the parent space.
		parent_space = nullptr; //Set to null.
	}

	//if (space != nullptr) //Check if space exists.
	//{
		//space->parent_space = nullptr; //Reset this.
		//delete space; //Delete space.

		//Right, so, since this is actually a 10x10x10 array... //TODO: Not sure if this is neccessary. I'll have to read up on it.
		//NOTE: MOVED INTO A SEPERATE FUNCTION.
		/*for (int x = 0; x < SPACE_SIZE; ++x)
		{
			for (int y = 0; y < SPACE_SIZE; ++y)
			{
				for (int z = 0; z < SPACE_SIZE; ++z)
				{
					if (space[x][y][z]) //If the space at the specified location exists (not equal to null)
					{
						space[x][y][z]->parent_space = nullptr; //Hide its parent (this space) from it.
						delete space[x][y][z]; //Delete it.
						space[x]][y][z] = nullptr; //Reset it.
					}
				}
			}
		}

	//	delete space; //Now finally delete this entire shabang. //TODO: This may not be needed. Remove it causes crashes.*/

	//	deleteSpace(space);
	//	space = nullptr;
	//}
	deleteSpaceVectorContents(space); //Delete all the spaces found in the children space 3d vector.

	//Now we do a check each of its neighbors and delete the ones that exist.
	/*if (left != nullptr)
	{
		left->parent_space = nullptr; //First, reset this.

		//Delete and reset. //NOTE: This is obsolete since it's now a 10x10x10 array rather than a tree thing.
		//delete left;
		//left = nullptr;
	}

	if (right != nullptr)
	{
		right->parent_space = nullptr; //First, reset this.

		//Delete and reset. //NOTE: This is obsolete since it's now a 10x10x10 array rather than a tree thing.
		//delete right;
		//right = nullptr;
	}

	if (up != nullptr)
	{
		up->parent_space = nullptr; //First, reset this.

		//Delete and reset. //NOTE: This is obsolete since it's now a 10x10x10 array rather than a tree thing.
		//delete up;
		//up = nullptr;
	}

	if (down != nullptr)
	{
		down->parent_space = nullptr; //First, reset this.

		//Delete and reset. //NOTE: This is obsolete since it's now a 10x10x10 array rather than a tree thing.
		//delete down;
		//down = nullptr;
	}

	if (above != nullptr)
	{
		above->parent_space = nullptr; //First, reset this.

		//Delete and reset. //NOTE: This is obsolete since it's now a 10x10x10 array rather than a tree thing.
		//delete above;
		//above = nullptr;
	}

	if (below != nullptr)
	{
		below->parent_space = nullptr; //First, reset this.

		//Delete and reset. //NOTE: This is obsolete since it's now a 10x10x10 array rather than a tree thing.
		//delete below;
		//below = nullptr;
	}*/

	dimension = nullptr;
	cluster = nullptr;
	galaxy = nullptr;
	solar_system = nullptr;
	celestial_body = nullptr;
	sector = nullptr;
	region = nullptr;

	//Delete and reset the model, if it exists.
//	if (model)
//	{
//		d3d.removeModel(model); //Remove the model from d3d.
//		delete model;
//		model = nullptr;
//	}

	//----------GAME SPECIFIC CODE BELOW----------
	sprite = nullptr;
} //Space::~Space()

void Space::genNeighbors()
{
	/* ***************** BEGIN OBSOLETE CODE ***************** */
	//Generate all of the space's neighbors.

	//Assume this is the top left space and that none of its neighbors exists.
	/*if (left != nullptr || right != nullptr || up != nullptr || down != nullptr || above != nullptr || below != nullptr)
	{
		std::cout << "Error: Space::genNeighbors failed: a neighbor already exists!\n";
		throw; //We just can't have none of this, dawg.
	}*/

	//Okay to proceed.

	/*
	Alright, here's the battle plan.

	Same as subdivide(). Tower first, column next, row last.
	*/

	/*Space *start_of_tower = this;
	Space *current = this; //The current space.

	for (int x = 0; x < SPACE_SIZE; ++x) //Row.
	{
		for (int y = 0; y < SPACE_SIZE; ++y) //Column.
		{
			for (int z = SPACE_SIZE; z > 0; --z) //Tower.
			{
				below = new Space; //Allocate memory for the space.
				current = below; //Move on to it.
				current->parent = this->parent; //Set the parent.
			}

			current = start_of_tower; //Go back to the top of the tower.

			down = new Space; //Allocate memory for down.
		}
	}*/

	/*long spaces_to_gen = SPACE_SIZE * SPACE_SIZE * SPACE_SIZE; //Store how many spaces it is to generate.

	std::cout << "\nGenerating " << spaces_to_gen << " spaces.\n"; //Just some debugging/informative output.

	Space *spaces[SPACE_SIZE][SPACE_SIZE][SPACE_SIZE]; //A temporary array thing to make this job manageable.

	//std::cout << "Test.\n";

	long x = 0;
	long y = 0;
	long z = SPACE_SIZE - 1; //- 1 since we're working with arrays and everything is shifted a value lower such that the first space is not accessed via [1] but via [0]. Basic c++ knowledge!

	//int i = 0; //For making sure all the spaces are generated.

	//The following allocates the memory of all of the spaces.
	for (long a = 0; a < SPACE_SIZE; ++a) //a = x. This is moving through the row.
	{
		for (long b = 0; b < SPACE_SIZE; ++b) //b = y. This is moving through the column.
		{
			for (long c = SPACE_SIZE; c > 0; --c) //This is moving through the tower.
			{
				//std::cout << "[" << a << "][" << b << "][" << c << "]\n"; //DEBUGGING: Output current position.
				if (a == 0 && b == 0 && c == SPACE_SIZE) //This space is this space.
				{
					//Do nothing.
					spaces[a][b][c] = this; //Set it to point to this.
					//std::cout << "'this' found.\n";
				}
				else //Not this space, and thus not already allocated.
				{
					spaces[a][b][c] = new Space; //Allocate memory for this space.
				}

				//++i; //For making sure all the spaces are generated.
			}
		}
	}

	//std::cout << "i = " << i << "\n";

	std::cout << "\nDone allocating.\n\n";

	Space *current = nullptr; //The current space.

	for (x = 0; x < SPACE_SIZE; ++x) //Move through the row.
	{
		for (y = 0; y < SPACE_SIZE; ++y) //Move through the column.
		{
			for (z = SPACE_SIZE; z > 0; --z) //This is moving through the tower.
			{
				//std::cout << "[" << x << "][" << y << "][" << z << "]\n"; //DEBUGGING: Output current position.

				current = spaces[x][y][z]; //Set the current space.

				if (x == 0 && y == 0 && z == SPACE_SIZE - 1) //This space is this space.
				{
					spaces[x][y][z] = this; //Point the current space to it.
				}
				else //Not this space.
				{
					//Everything in here is only applicable to the space that's not this space.
					current->parent_space = this->parent_space; //Set the space's parent.
				}

				if (x > 0)
				{
					current->left = spaces[x - 1][y][z]; //Set its left neighbor.
				}
				if (x < SPACE_SIZE - 1)
				{
					current->right = spaces[x + 1][y][z]; //Set its right neighbor.
				}
				if (y < SPACE_SIZE - 1)
				{
					current->down = spaces[x][y + 1][z]; //Set its down neighbor.
				}
				if (y > 0)
				{
					current->up = spaces[x][y-1][z]; //Set its up neighbor.
				}
				if (z > 0)
				{
					current->below = spaces[x][y][z-1]; //Set its below neighbor.
				}
				if (z < SPACE_SIZE - 1)
				{
					current->above = spaces[x][y][z+1]; //Set its up neighbor.
				}
			}
		}
	} */

	/* ***************** END OBSOLETE CODE ***************** */

	//TODO: Not sure what to replace it with...

	std::cout << "Done setting neighbors and stuff (THIS IS PROBABLY OBSOLETE).\n";
}

void Space::genChildren(bool fromGenParent)
{
	for (int X = 0; X < SPACE_SIZE; ++X)
	{
		for (int Y = 0; Y < SPACE_SIZE; ++Y)
		{
			for (int Z = 0; Z < SPACE_SIZE; ++Z)
			{
				if (!this->space[X][Y][Z]) //If it doesn't exist, make it exist.
				{
					this->space[X][Y][Z] = new Space; //Allocate the space.
					Space *current = this->space[X][Y][Z]; //Set current to the space so that I can type it easier.

					//Set coordinates.
					current->x = X;
					current->y = Y;
					current->z = Z;

					current->parent_space = this; //Set the current space's parent space.
				}
				else
				{
					Space *current = this->space[X][Y][Z]; //Set current to the space so that I can type it easier.
					current->parent_space = this; //Set the current space's parent space.
				}
			}
		}
	}
}

void Space::subdivide(int X, int Y, int Z, long count)
{
	//TODO: Improve the space generation to cover all needed children.
	count--; //Deincrement this.

	if (count < 1)
	{
		return; //Abort. No use to continue. It's done. The end has been reached.
	}

	//space[X][Y][Z] = new Space; //Allocate memory for the children.
	//space[X][Y][Z]->parent_space = this; //Set the parent.
	//space[X][Y][Z]->genNeighbors(); //Generate its neighbors. //TODO: I think this is obsolete.

	/* ***************** BEGIN OBSOLETE CODE ***************** */
	//if (count > 1)
	//{
		//Subdivide children.

		/*
		It works like this:
		The uppermost back left corner is the starting space.
		||
		\/
		All the space vertically down from it are generated.
		Then
		||
		\/
		It moves on to the one horizontally below the starting one, towards the camera, so to say.
		It does that for the whole column horizontally.
		Then it moves down on to the next member in the row.
		*/

		//Let's refer to every line vertically as towers.
		/*Space *start_of_tower = space; //A pointer to the starting space.
		//Space *start_of_row = space; //The start of the row. Doesn't seem this is needed.
		Space *start_of_column = space; //The start of the column.
		Space *current = space; //The current space.

		for (int x = 0; x < SPACE_SIZE; ++x) //Then finally do the row.
		{
			//Then do the column.
			for (int y = 0; y < SPACE_SIZE; ++y)
			{
				//Do each tower first.
				for (int z = SPACE_SIZE; z > 0; --z)
				{
					current->subdivide(count); //Subdivide this child.
					//Move on to the next one.
					current = current->below; //Which is down below it; we're doing towers now.
					if (current == nullptr)
					{
						std::cout << "Debug: Reached end of the tower.\n"; //This is just a debug check to make sure the loop's designed correctly.
					}
				}

				current = start_of_tower; //Move back up to the top of the tower.
				current = current->down; //Move on to the next one in the column.
				start_of_tower = current; //Set the current.
			}

			current = start_of_column; //Move back up to the start of the column.
			current = current->right; //Move on to the next one in the row.
			start_of_column = current; //Set the current.
		}

		//Done with all that.
	}*/
	/* ***************** END OBSOLETE CODE ***************** */

	if (count > 0)
	{
		if (!space[X][Y][Z]) //If space does not exist.
		{
			//space[x][y][z] = new space(this); //Generate the new space, with this as its parent. //TODO: Implement Space::Space(Space _parent_space);
			space[X][Y][Z] = new Space; //Generate this space.
			space[X][Y][Z]->parent_space = this; //Set the parent space.
		}

		space[X][Y][Z]->subdivide(X, Y, Z, count); //Subdivide this child. //TODO: Make it handle generating a child at a different x, y, and z? And possibly multiple?
	}
}

void Space::genParent(long count)
{
	count--; //Deincrement this.

	if (count < 0) //Check if it reached the end.
	{
		return; //Abort. Did them all.
	}

	if (parent_space != nullptr) //Already has a parent.
	{
		std::cout << "Warning: Parent already exists. Continuing anyway. Maybe the upper parents don't exist.\n"; //Complain, but continue.

		if (count > 1) //If it should keep going.
		{
			parent_space->genParent(count); //Recurse upwards. Maybe the upper parents don't exist.
		}
	}
	else
	{
		parent_space = new Space; //Allocate memory for the parent space.
		parent_space->space[x][y][z] = this; //Tell the parent space this space is its child space.
		//TODO: Properly assign these...
		parent_space->x = (SPACE_SIZE / 2);
		parent_space->y = (SPACE_SIZE / 2);
		parent_space->z = (SPACE_SIZE / 2);

		//parent_space->genNeighbors(); //Generate the neighbors of the parent space. //TODO: I think this is obsolete?
		//parent_space->genChildren(true); //Generate its children.

		if (count > 1) //If it should keep going.
		{
			parent_space->genParent(count); //Recurse upwards.
		}
	}
}

/*Space *Space::moveToCoords(int x, int y, int z)
{
	//First: savety checks.
	if (x < 0 || x >= SPACE_SIZE || y < 0 || y >= SPACE_SIZE || z < 0 || z >= SPACE_SIZE)
	{
		std::cout << "Error: x, y, or z out of bounds in Space::moveToCoords().\n";
	}

	Space *current = space; //Set the current.

	for (int a = 0; a < x; ++a)
	{
		for (int b = 0; b < y; ++b)
		{
			for (int c = SPACE_SIZE; c > z; --c)
			{
				current = current->below; //Move down.
			}

			current = current->down; //Move down.
		}

		current = current->right; //move right.
	}
}*/

/*Space *Space::moveToCoordsOnSameLevel(int x, int y, int z)
{
	//First: savety checks.
	if (x < 0 || x >= SPACE_SIZE || y < 0 || y >= SPACE_SIZE || z < 0 || z >= SPACE_SIZE)
	{
		std::cout << "Error: x, y, or z out of bounds in Space::moveToCoordsOnSameLevel().\n";
	}

	Space *current = parent_space->space; //Set the current.

	for (int a = 0; a < x; ++a)
	{
		for (int b = 0; b < y; ++b)
		{
			for (int c = SPACE_SIZE; c > z; --c)
			{
				current = current->below; //Move down.
			}

			current = current->down; //Move down.
		}

		current = current->right; //move right.
	}
}*/

void Space::setMolecule(Molecule &molecule)
{
	if (molecules)
	{
		delete molecules; //Delete, if it exists.
	}

	molecules = new Molecule; //Allocate memory for the molecule.

	molecules->set(molecule); //Set the molecule.
}

Space* Space::left()
{
	if (!parent_space) //Can only have neighbors if parent space exists, so check if it exists.
	{
		std::cout << "\n[ws::Space::left()] Generating parent.\n";
		this->genParent();
	}

	return parent_space->getChild(x - 1, y, z);
}

Space* Space::right()
{
	if (!parent_space) //Can only have neighbors if parent space exists, so check if it exists.
	{
		std::cout << "\n[ws::Space::right()] Generating parent.\n";
		this->genParent();
	}

	return parent_space->getChild(x + 1, y, z);
}

Space* Space::up()
{
	if (!parent_space) //Can only have neighbors if parent space exists, so check if it exists.
	{
		std::cout << "\n[ws::Space::up()] Generating parent.\n";
		this->genParent();
	}

	return parent_space->getChild(x, y - 1, z);
}

Space* Space::down()
{
	if (!parent_space) //Can only have neighbors if parent space exists, so check if it exists.
	{
		std::cout << "\n[ws::Space::down()] Generating parent.\n";
		this->genParent();
	}

	return parent_space->getChild(x, y + 1, z);
}

Space* Space::above()
{
	if (!parent_space) //Can only have neighbors if parent space exists, so check if it exists.
	{
		std::cout << "\n[ws::Space::above()] Generating parent.\n";
		this->genParent();
	}

	return parent_space->getChild(x, y, z + 1);
}

Space* Space::below()
{
	if (!parent_space) //Can only have neighbors if parent space exists, so check if it exists.
	{
		std::cout << "\n[ws::Space::below()] Generating parent.\n";
		this->genParent();
	}

	return parent_space->getChild(x, y, z - 1);
}

Space* Space::getChild(int X, int Y, int Z)
{
	if (X < 0)
	{
		//Requested space is to the left. Delegate this task to that space.
		//if (this->left()) //This check ensures it doesn't crash due to trying to work with a nonexistant space.
		//{
			return this->left()->getChild((X + SPACE_SIZE), Y, Z);
		//}
		//else
		//{
			//Blar, left don't exist. Forget about it.
		//	return nullptr;
		//}
	}
	else if (X >= (SPACE_SIZE)) //TODO: If this crashes or if it's skipping rendering spaces, play around with: >, >=, SPACE_SIZE -1, etc.
	{
		//Requested space is to the right. Same drill as above.
		if (this->right()) //This check ensures it doesn't crash due to trying to work with a nonexistant space.
		{
			return this->right()->getChild((X - SPACE_SIZE), Y, Z);
		}
		else
		{
			//Blar, right don't exist. Forget about it.
			return nullptr;
		}
	}

	if (Y < 0)
	{
		//Requested space is up. Same drill as above.
		if (this->up()) //This check ensures that it doesn't crash due to trying to work with a nonexistant space.
		{
			return this->up()->getChild(X, (Y + SPACE_SIZE), Z);
		}
		else
		{
			//Blar, up one doesn't exist. Forget about it.
			return nullptr;
		}
	}
	else if (Y >= (SPACE_SIZE))
	{
		//Requested space is down. Same drill as above.
		if (this->down())
		{
			return this->down()->getChild(X, (Y - SPACE_SIZE), Z);
		}
		else
		{
			return nullptr;
		}
	}

	if (Z < 0)
	{
		//Requested space is below. Same drill as above.
		if (this->below())
		{
			return this->below()->getChild(X, Y, (Z + SPACE_SIZE));
		}
		else
		{
			return nullptr;
		}
	}
	else if (Z >= (SPACE_SIZE))
	{
		//Requested space is above. Same drill as above, except this isn't specifically a mining game.
		if (this->above())
		{
			return this->above()->getChild(X, Y, (Z - SPACE_SIZE));
		}
		else
		{
			return nullptr;
		}
	}
	//So using this method, it doesn't matter if the requested space is several spaces above, to the left, and up of this space. It'll keep moving towards the appropiate space, then finally do the work on that space and return the pointer. Finally the first space that had this function called will return the pointer to the caller. Simple!

	//If it gets this far, that means the space is one of its children.

	if (!space[X][Y][Z])
	{
		//Space doesn't exist. Allocate it.
		space[X][Y][Z] = new Space;
		Space *current = this->space[X][Y][Z]; //Set current to the space so that I can type it easier.

		//Set coordinates.
		current->x = X;
		current->y = Y;
		current->z = Z;

		current->parent_space = this; //Set the current space's parent space.
	}

	return space[X][Y][Z];
}

void Space::addEntity(Entity *entity)
{
	std::vector<Entity* >::iterator *iter;
	iter = GEngine::mdata::inVector(entities, entity);
	if (!iter) //Proceed if the entity is not already in entities. iter = nullptr if it didn't find the entity in the vector.
	{
		entities.push_back(entity); //Add the entity.
	}
	else
	{
		delete iter; //Delete to avoid memleak. TODO: This is temporary until I do something to make the value free itself when it's no longer needed. (Shared pointer, anyone?)
	}
}

void Space::removeEntity(Entity *entity)
{
	std::vector<Entity* >::iterator *iter;
	iter = GEngine::mdata::inVector(entities, entity);
	if (iter) //Can proceed only if iter actually exists.
	{
		//entity->container_space = nullptr; //TODO: Handle multitle entities. //For now, I'll leave this to the caller.
		entities.erase((*iter)); //Erase the entity.
	}
}

void deleteSpace(Space *space)
{
	//TODO: Figure out what's up with this function and if there's even any use to it.
	/*if (space->space) //If the space has children.
	{
		for (int x = 0; x < SPACE_SIZE; ++x)
		{
			for (int y = 0; y < SPACE_SIZE; ++y)
			{
				for (int z = 0; z < SPACE_SIZE; ++z)
				{
					if (space->space[x][y][z]) //If the space at the specified location exists (not equal to null)
					{
						space->space[x][y][z]->parent_space = nullptr; //Hide its parent (this space) from it.
						delete space->space[x][y][z]; //Delete it.
						space->space[x][y][z] = nullptr; //Reset it.
					}
				}
			}
		}

		//delete space->space; //Now finally delete the child. //TODO: This may not be needed. Remove if it causes crashes.
		//space->space = nullptr; //Set to null.
	}*/
	//deleteSpaceVectorContents(space->space); //Delete all the children. //TODO: Commenting this line out becaues Space::space is now private. Is there even a use for this function?

	delete space; //Finally, delete the space itself.
}

void deleteSpaceVectorContents(std::vector<std::vector<std::vector<Space* > > > &space) //Delete all the spaces found in the children space 3d vector.
{
	for (int x = 0; x < SPACE_SIZE; ++x)
	{
		for (int y = 0; y < SPACE_SIZE; ++y)
		{
			for (int z = 0; z < SPACE_SIZE; ++z)
			{
				if (space[x][y][z]) //If the space at the specified location exists (not equal to null)
				{
					space[x][y][z]->parent_space = nullptr; //Hide its parent (this space) from it.
					delete space[x][y][z]; //Delete it.
					space[x][y][z] = nullptr; //Reset it.
				}
			}
		}
	}

	//Vector is now completely empty!
}

//----------GAME SPECIFIC CODE BELOW----------
void Space::render(GEngine::mgfx::d2d::D2D &d2d, int X, int Y, GEngine::mgfx::d2d::Sprite *no_sprite, sf::Font &font, float rescaleto_width, float rescaleto_height, bool overlay)
{
	if (sprite) //If the sprite exists...
	{
		sprite->sprite->setScale((float)(rescaleto_width / (float)sprite->getWidth()), (float)(rescaleto_height / (float)sprite->getHeight()));
		sprite->draw(d2d, X, Y);
	}
	else if (no_sprite)
	{
		no_sprite->draw(d2d, X, Y);
		//TODO: Draw the "x, y" text thing.
	}
	if (overlay)
	{
		std::stringstream ss;
		ss << "(" << x << ", " << y << ", " << z << ")";
		d2d.window->renderText(ss.str(), X, Y, 8, font);
	}
	//TODO: In both cases, draw "x,y" (not "X, Y") on this space.
	//That is just a temp feature. Permanent version might be something along the lines of drawing the "x, y" thing only on spaces that don't have a sprite (that'd be pretty cool).

	if (entities.size())
	{
		std::vector<Entity* >::iterator iter = entities.begin();
		for (; iter != entities.end(); ++iter)
		{
			(*iter)->render(d2d, X, Y); //TODO: Proper rendering for the entity. Also: Support multi-space entities.
		}
	}
}

} //namespace ws
