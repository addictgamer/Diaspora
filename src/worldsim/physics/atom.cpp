/* Copyright Ciprian Ilies */

#include "atom.hpp"

#include "molecule.hpp"

namespace ws
{

Atom::Atom()
{
	parent_molecule = nullptr;
}

Atom::~Atom()
{
	if (parent_molecule)
	{
		parent_molecule->atoms = nullptr; //Let the parent molecule know that this atom is now gone.

		parent_molecule = nullptr; //Reset this.
	}
}

Atom *ATOM_IRON = nullptr; //Iron atom.

bool setupAtoms()
{
	ATOM_IRON = new Atom; //Allocate memory for it.

	return true; //Success.
}

} //namespace ws
