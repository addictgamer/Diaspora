/* Copyright Ciprian Ilies */

#pragma once

#include "../internal_header.hpp"

#include "measurements.hpp"

/*
I'm not all too sure what out there is a subatomic particle besides photons, electrons, neutrons, neutrinos, antineutrinos, protons, etc.
Regardless, it's the stuff under the atomic level of the universe. Still not the lowest level.
*/

/*
Data table for best available measurements, properties, and behaviour for known particles:

***Electron***

Composition:
	Elementary Particle, though some theories give it a substructure. However, no substructure has yet been discovered.

Generation:
	First generation, Leptop. Fermionic.

Spin:
	Up or Down -- 1/2h (h = planck constant) or -1/2h.

Charge:
	-1 elementary electric charge
	or
	−1.602176565 × 10^−19 coulombs
	(negative charge)	(Note that this is the same value, opposite sign, as the proton)

Mass:
	1/1836 of a proton
	or
	9.10939 x 10^-31 kilograms

Diameter:
	1/1000th the diameter of a proton.
	or
	2.82 × 10^-33 centimeters (best available measurement)
	or
	An upper limit of 20^-22 meters.
	I really don't know. Some scientists believe it's a point particle.

Binding force to the atom:
	Electrostatic force.

Force Interactions:
	Gravity, Electromagnetic, Weak.

Antiparticle:
	Positron (aka antielectron).

Behaviour with other Particles:
	Electrons:
		Shoot photons at each other. When the other electron absorbs the photon, it changes direction.
	Positron:
		Anihlates with Positrons to produce gamma rays.

***Proton***

Composition:
	Supposedly 2 up quarks and a down quark. Who knows what it actually is. I'll just go with it and figure out how the universe actually works as I go.

Charge:
	1 elementary electric charge
	or
	1.602176565 × 10^-19 coulumbs
	(positive charge)	(Note that this is the same value, opposite sign, as the electron)

Mass:
	1.672621777 × 10^−27 kg

Diameter:
	1.7 × 10^-15 meters

Force Interactions:
	Gravity, Electromagnetic, Weak, Strong

Antiparticle:
	Antiproton

***Neutron***

Copmosition:
	Supposedly 2 down quarks and one up quark. Who knows?

Charge:
	None.

Mass:
	1.674927351×10^−27 kg

Diameter:
	1.9 × 10^-15 meters

Force Interactions:
	Gravity, Electromagnetic, Weak, Strong

Antiparticle:
	antineutron

***Photon***

Composition:
	Elementary Particle, though I doubt it.

Mass:
	0 (Really? Maybe. I don't know)

Charge:
	None.

Diameter:
	It's a wave, remember. Bah humbug. I never liked quantum mechanics. Anyway, wavelength determines size.

Force Interactions:
	Electromagnetic

Force Carrier of:
	Electromagnetic force

It's also a particle. That whole wave-particle duality thing. I don't like it. People just choose the one that works best for their situation. I don't consider that science. There has to be something we're missing.

*/

namespace ws
{

class SubatomicParticle
{
public:
	Charge charge; //The charge of the particle.

	Mass mass; //The mass of the particle.

	Distance diameter; //The diameter of the particle. Perhaps using radius would be better? I'll see once we get to that stage.

	bool elementary_particle; //False if it has substructure. Should automatically be determined by whether or not it has a vector/list of composing particles.

	SubatomicParticle(); //Constructor.
	~SubatomicParticle(); //Deconstructor.
};

extern SubatomicParticle electron;
extern SubatomicParticle proton;
extern SubatomicParticle neutron;
extern SubatomicParticle photon;

void setupParticles(); //Sets up all the built-in particles.

} //namespace ws
