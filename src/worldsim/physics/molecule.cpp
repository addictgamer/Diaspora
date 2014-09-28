/* Copyright Ciprian Ilies */

#include "molecule.hpp"

#include "atom.hpp"

#include <iostream>

namespace ws
{

Molecule::Molecule()
{
	atoms = nullptr;
}

Molecule::~Molecule()
{

	//If it has atoms, delete them.
	if (atoms)
	{
		atoms->parent_molecule = nullptr; //Tell it that it doesn't have a parent.
		delete atoms; //Delete the atoms.
		atoms = nullptr; //Reset to a nullptr;
	}

}

void Molecule::addAtomFromType(Atom &atom)
{
	//TODO: Change this later on to actually add an atom.

	if (atoms) //For now, if there are atoms, abort. REMEMBER, CHANGE THIS BEHAVIOUR.
	{
		std::cout << "Error: failed to add atom: atoms already exist.\n";
		throw; //TODO: Proper error handling.
	}

	atoms = new Atom; //Allocate memory for atoms.

	atoms->parent_molecule = this; //Set its parent molecule.

	//Ya, there's nothing to copy right now...
}

void Molecule::set(Molecule &molecule)
{
	//For now, there's nothing to set besides the atom...

	addAtomFromType(*molecule.atoms); //So, ya, copy over the atom. Or something. Not sure how to do this. Have every atom point to its original type? Naw, sounds bad.
}

Molecule *MOLECULE_IRON = nullptr;

bool setupMolecules()
{
	if (!ATOM_IRON) //Atoms need to be set up already.
	{
		std::cout << "Error: Atoms need to be set up to set up molecules.\n";
		return false; //Abort. TODO: Proper error handling.
	}

	if (MOLECULE_IRON) //If the molecule already exists.
	{
		std::cout << "Error: Molecules already set up? This should not happen...\n";
		return true; //Abandon ship. TODO: Proper error handling.
	}

	MOLECULE_IRON = new Molecule; //Allocate memory for it.

	MOLECULE_IRON->addAtomFromType(*ATOM_IRON); //Copy over iron's properties.

	return true; //Success!
}

} //namespace ws
