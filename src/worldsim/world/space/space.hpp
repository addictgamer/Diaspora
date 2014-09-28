/* Copyright Ciprian Ilies */

#pragma once

#include <vector>
#include <iostream>

#include <GEngine/GEngine.hpp>

#include "../../internal_header.hpp"
#include "../../physics/molecule.hpp"
#include "../../../game/game.hpp"

namespace ws
{

class Dimension;
class Cluster;
class Galaxy;
class SolarSystem;
class CelestialBody;
class Sector;
class Region;
class Entity;
class Molecule;

//Space's dimensions: 10x10x10 children. So 1000 children.
//NOTE: Might want to change to 2x2x2...8 children is a lot cheaper than 1000 children. On the other hand, that complicates things unnecessarily.
static const int SPACE_SIZE = 10;

//TODO: Make use of wonderful smart pointers.
class Space
{
private:
	//Children. Allows for the RCMS.
	//Stored in a three dimensional 10 element each array.
	//Some children may be uninitialized to conserve memory.
	//Space *space;
	//ACCESS SPACE VIA THE getChild() FUNCTION.
	std::vector<std::vector<std::vector<Space* > > > space; //TODO: Try my hand at a pointer version sometime? Whatever. //TODO: Use the one dimensional pointer array idea. Maybe.
public:
	//Actually, I'll make it one array that emaluates being three dimensional.
	//Actually, nevermind. I'll have to think more about this.

	//The space's parent space.
	//If nullptr, that means that this space is at the top of the hierarchy (and thus acts as a tile).
	Space *parent_space;

	//Used only for determining its position in its parent space's 10x10x10 array containing it.
	unsigned int x, y, z;
	//Neighboring space.
	//Space *left, *right, *up, *down, *above, *below; //TODO: Replace with functions?

	//The second set of children. Since the cosmos are simulated as space, the galaxies, clusters, galaxies, solar systems, and celestial bodies are stored directly in it.
	//So, on the highest level of space, it points to all clusters, rogue galaxies, rogue solar systems rogue celestial bodies, etc.
	//Going lower and level it splits up to see the innards of the galaxies.
	Dimension *dimension;
	Cluster *cluster;
	Galaxy *galaxy;
	SolarSystem *solar_system;
	CelestialBody *celestial_body;
	Sector *sector;
	//The above can mostly be ignored. Those are only for psudo-simulation purposes.
	//The region is the real deal.
	Region *region;

	//Its parent region.
	Region *parent_region;

	//A vector of entity references.
	//This serves the purpose of pointing to all entities in the space. Only used in the top hierarchy of the space.
	//TODO: Make this use better pointers.
	std::vector<Entity *> entities;

	//Right, so...Composition of the space and stuff.
	//Not sure how to do this. We'll see...
	//NOTE: Look at src/worldsim/physics/molecule.hpp for relevant discussion.
	//For now, it's just a singular molecule.
	Molecule *molecules; //The molecules.

	Space();
	~Space();

	//Space(Space &_parent_space); //Overloaded constructor meant to assign parent space right off the bat.

	//Generates the neighbors of this space.
	//NOTE: Assumes that none of its neighbors already exist.
	//NOTE: It only allocates empty space.
	//NOTE: It assumes that this is the top left corner of the space.
	void genNeighbors();

	//The complement of the above function.
	//All it does it generate all of this space's children.
	//bool fromGenParent tells it that it's coming from the genParent() function.
	//This has the implication that all the children spaces only need their parent pointer set, or something along those lines. //TODO: THIS IS PROBABLY REDUNDANT.
	//TODO: Make a seperate allocate_children functionality.
	void genChildren(bool fromGenParent = false);

	//Divides the space into a 10x10x10 region of cubes.
	//Make use of the count variable to recursively split the children.
	//Count = 1 = only this one. Count = 0 = none, a waste of function call.
	//Count > 1 = subdivide that many times.
	//WARNING: It will subdivide ALL the children. So it will grow exponentially (or more?) in resource usage.
	//NOTE: It only allocates empty space.
	void subdivide(int X = 0, int Y = 0, int Z = (SPACE_SIZE - 1), long count = 1);

	//The complement of the above function.
	//It recursively generates parents up and up and up and up and away we go! Hahaha. Comment writing can be fun sometimes.
	//NOTE: It only allocates empty space.
	void genParent(long count = 1);

	//Returns the child space at the specified coordiantes.
	//Returns nullptr if out of bounds or no children.
	//NOTE: THIS IS OBSOLETE.
	//Space *moveToCoords(int x, int y, int z);

	//Complement of the above.
	//It returns the space at the specified coordinates at the same level of the cube map system as this space.
	//Returns nullptr if out of bounds.
	//NOTE: THIS IS OBSOLETE.
	//Space *moveToCoordsOnSameLevel(int x, int y, int z);

	/*
	Sets the space's molecule(s).
	Takes the parameter as a copy.
	Parameters:
		Molecule *molecule : the molecule.
	*/
	void setMolecule(Molecule &molecule);

	//TODO: Parameter specifying if nonexistant space should be created.
	Space* left(); Space* right(); Space* up(); Space* down(); Space* above(); Space* below();

	/*
	 * Returns a pointer to the child at specified x, y, and z.
	 * Automatically resolves cases like "oh, this isn't in this space."
	 */
	Space* getChild(int X, int Y, int Z);

	/******Entity related functions below******/

	void addEntity(Entity *entity);
	void removeEntity(Entity *entity);

	//----------GAME SPECIFIC CODE BELOW----------
	GEngine::mgfx::d2d::Sprite *sprite; //The space's sprite (if any).
	//Render the space.
	//You'll have to provide the coordinates & d2d yourself. The last parameter specifies what sprite to draw if the space doesn't have its own.
	void render(GEngine::mgfx::d2d::D2D &d2d, int X, int Y, GEngine::mgfx::d2d::Sprite *no_sprite, sf::Font &font, float rescaleto_width, float rescaleto_height, bool overlay = true);
};

//Deletes the space passed to it. Needed in an older system, kinda obsolete now.
//Whatever. We'll see if we need it.
void deleteSpace(Space *space);

//Deletes Space.space (the vector vector vector aka 3d vector). Or rather, its contents. All those spaces.
void deleteSpaceVectorContents(std::vector<std::vector<std::vector<Space* > > > &space);

} //namespace ws
