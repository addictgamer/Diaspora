/* Copyright Ciprian Ilies */

#pragma once

#include "../internal_header.hpp"

/*
A molecule is a construct of atoms and other molecules to create a molecule.
It's just a collection of bound atoms and molecules with different forces at work causing the bonding.
Which forces are at work and what atoms are bound together determine what the molecular compound is and how it interacts with the world.
*/

namespace ws
{

class Atom; //Forward declaration.

//Holds molecule specific stuff.
namespace molecule
{

//Well, here's how atoms are stored:
//Sort of like a linked web.
//Each neighbor has pointers to other neighbors which stores data like direction, distance, bonds, whatever.
/*class AtomicNeighbor
{
public:
	Atom *atom; //Pointer to the atom it represents.
	Distance *distance; //The distance 

	AtomicNeighbor *neighbors; //Its neighbors. //TODO: How does this? Dynamic array? New class AtomicNeighbors? BLARG. I think the former.

	AtomicNeighbor();
	~AtomicNeighbor();
};*/
//No, that won't work properly.
//I need stuff:
//1. The list itself.
//2. Each entry in the list needs to point to an atom, and then have a list of all its neighbors. Each neighbor thingy containing a pointer to the actual atom, the distance between these two atoms, direction, how they're interacting with each other and whatever.
//3. And, uh, stuff.

} //namespace molecule

class Molecule
{
public:
	//List of atoms.
	//I want a 3D map of atoms. I think. How do I do this? And all those bonds...I'm going to refer to my chemistry book again.

	Atom *atoms; //TODO: For now, just hold a singular atom until I get the rest sorted out.

	Molecule(); //Constructor.
	~Molecule(); //Deconstructor.

	//Copies the properties of atom and applies it to a new atom that will be added to atoms.
	void addAtomFromType(Atom &atom);

	//Sets the properties of this molecule to be like the molecule referenced.
	void set(Molecule &molecule);
};

extern Molecule *MOLECULE_IRON; //An iron molecule.

bool setupMolecules(); //Sets up all the predefined molecules.

} //namespace ws
