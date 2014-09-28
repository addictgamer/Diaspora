/* Copyright Ciprian Ilies */

#include "subatomic_particle.hpp"

#include <iostream>

namespace ws
{

SubatomicParticle::SubatomicParticle()
{
	elementary_particle = true;
}

SubatomicParticle::~SubatomicParticle()
{
}

void setupParticles()
{
	std::cout << "Setting up particles.\n\n";

	//First up is the electron.

	electron.elementary_particle = true; //Elementary particle.

	electron.charge.set(-1.602176565f, -19); //Set the charge.

	std::cout << "Set Electron charge to: " << electron.charge.makeString() << "\n";

	electron.mass.set(9.10939f, -34); //Set the mass.

	std::cout << "Set Electron mass to: " << electron.mass.makeString() << "\n";

	electron.diameter.set(2.82, -33); //Set the diameter.

	std::cout << "Set Electron diameter to: " << electron.diameter.makeString() << "\n";

	std::cout << "\n"; //For formatting purposes.

	//Now the proton.

	proton.elementary_particle = false; //Not an elementary particle.

	proton.charge.set(1.602176565f, -19); //Set the charge.

	std::cout << "Set Proton charge to: " << proton.charge.makeString() << "\n";

	proton.mass.set(1.672621777, -30); //Set the mass.

	std::cout << "Set Proton mass to: " << proton.mass.makeString() << "\n";

	proton.diameter.set(1.7, -15); //Set the diameter.

	std::cout << "Set Proton diameter to: " << proton.diameter.makeString() << "\n";

	std::cout << "\n";

	//Now the neutron.

	neutron.charge.set(0, 0); //Set the charge.

	std::cout << "Set Neutron charge to: " << neutron.charge.makeString() << "\n";

	//neutron.mass.set(1.674927351, −30); //Set the mass.
	neutron.mass.set(1.674927351, -30); //Set the mass.

	std::cout << "Set Neutron mass to: " << neutron.mass.makeString() << "\n";

	neutron.diameter.set(1.9, -15);

	std::cout << "Set Neutron diameter to: " << neutron.diameter.makeString() << "\n";

	std::cout << "\n";

	//Now the photon.

	photon.elementary_particle = true; //Elementary particle.

	std::cout << "Set Photon's very limited set of properties.\n";

	std::cout << "\n";
}

SubatomicParticle electron;
SubatomicParticle proton;
SubatomicParticle neutron;
SubatomicParticle photon;

} //namespace ws
