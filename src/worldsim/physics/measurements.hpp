/* Copyright Ciprian Ilies */

#pragma once

#include "../internal_header.hpp"

//***WARNING*** Do NOT include any file here which includes this file. That will totally screw up the compiler and give "incomplete type" errors. I don't want that.

#include <string>

/*
Contains a bunch of data types and pertinent functions and classes.
*/

namespace ws
{

/*
This function returns the "kilo" in "kilogram" if the 'unit' part of a value based on what its value is.

0 = none
1	=	1 0					= deca
2	=	1 00					= hecto
3	=	1 000					= kilo
4	=	1 000 0					=
5	=	1 000 00				=
6	=	1 000 000				= mega
7	=	1 000 000 0				=
8	=	1 000 000 00				=
9	=	1 000 000 000				= giga
10	=	1 000 000 000 0				=
11	=	1 000 000 000 00			=
12	=	1 000 000 000 000			= tera
13	=	1 000 000 000 000 0			=
14	=	1 000 000 000 000 00			=
15	=	1 000 000 000 000 000			= peta
16	=	1 000 000 000 000 000 0			=
17	=	1 000 000 000 000 000 00		=
18	=	1 000 000 000 000 000 000		= exa
19	=	1 000 000 000 000 000 000 0		=
20	=	1 000 000 000 000 000 000 00		=
21	=	1 000 000 000 000 000 000 000		= zetta
22	=	1 000 000 000 000 000 000 000 0		=
23	=	1 000 000 000 000 000 000 000 00	=
24	=	1 000 000 000 000 000 000 000 000	= yotta

The value given is simply the number of zeros.

*/
std::string getUnitPrefix(long zero_count);

/*
Mass.

Components:
	value:
		The actual value of the thing. Say, the 1.2 part in 1.2 kg
	unit:
		The exponent in, say, 10^3 in 1.2x10^3 grams. Specifically, the "3". The number of zeros. 10^3 = 1000 which is 3 zeros.
	unit_suffix:
		The "gram" in "kilogram".
	plural_unit_suffix:
		Self explanatory. "grams" versus "kilograms".
	makeString():
		Combines the value, unit, and unit_suffix (or plural_unit_suffix accordingly) into a human readable string.
	getUnitName():
		Returns the unit name, say "gram" or "grams", depending on state of plurality. That is, singular = "gram", plural = "grams".
	set():
		Sets the value and unit with one handy function call. First parameter is the value, second is the unit.

Pass unit by itself to getUnitPrefix(). unit is really just the measure of how many zeros there are.
*/

class Mass
{
public:
	double value;
	long unit;

	std::string unit_suffix;
	std::string plural_unit_suffix;

	Mass();
	~Mass();

	std::string makeString();
	std::string getUnitName();

	void set(double _value, long _unit);
};

/*
Charge.

Refer to Mass's entry.
*/

class Charge
{
public:
	double value;
	long unit;

	std::string unit_suffix;
	std::string plural_unit_suffix;

	Charge();
	~Charge();

	std::string makeString();
	std::string getUnitName();

	void set(double _value, long _unit);
};

/*
Distances, such as diameter, radius, width, height, distance, etc.

Refer to Mass's entry.
*/

/*
I should mention some more distance measurements now. And after this class, I'll create a few conversion functions.


***Astronomical Measurements***

Parsec:

30.857 × 10^15 meters

*/

class Distance
{
public:
	double value;
	long unit;

	std::string unit_suffix;
	std::string plural_unit_suffix;

	Distance();
	~Distance();

	std::string makeString();
	std::string getUnitName();

	void set(double _value, long _unit);
};

/*
Converts parsecs to meters.

Returns result as a Distance. input is an input of type Distance.
Obviously, provide parsecs for input.
*/

Distance parsecsToMeters(Distance input);

/*
Converts meters to parsecs.

Returns result as a Distance. input is an input of type Distance. Provide meters for input.
*/

Distance metersToParsecs(Distance input);

} //namespace ws
