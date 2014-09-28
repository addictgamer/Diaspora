/* Copyright Ciprian Ilies */

#pragma once

#include "../internal_header.hpp"

/*
An atom is a construct of smaller subatomic and quantum particles which are combined together in a system to get the resulting thing on the higher level which we know as an atom.
The different properties of all the components of this system, the atom, govern what the atom is and its behaviour.
Even such simple things as the energy of the electrons in the system and the locations of them and the neutrons and the specific energies and compositions of the components of these components.
*/

namespace ws
{

//Forward declarations of used classes.
class Molecule;

class Atom
{
public:
	Molecule *parent_molecule; //The molecule that contains this.

	Atom(); //Constructor.
	~Atom(); //Deconstructor.
};

extern Atom *ATOM_IRON;

bool setupAtoms(); //Sets up all the predefined atoms.

} //namespace ws
