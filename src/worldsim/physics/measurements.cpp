/* Copyright Ciprian Ilies */

#include "measurements.hpp"

#include <iostream>

#include <GEngine/GEngine.hpp>

using namespace GEngine;

/* Refer to header for definitions and explanations of everything in here */

namespace ws
{

/* ***GENERIC FUNCTIONS*** */

std::string getUnitPrefix(long zero_count)
{
	//TODO: Do negatives and fill out the positives in between all the major ones provided by SI.
	switch(zero_count)
	{
		/* Smaller than base unit */
		case -24:
			return "yocto";
		case -21:
			return "zepto";
		case -18:
			return "atto";
		case -15:
			return "femto";
		case -12:
			return "pico";
		case -9:
			return "nano";
		case -6:
			return "micro";
		case -3:
			return "milli";
		case -2:
			return "centi";
		case -1:
			return "deci";
		//Base unit.
		case 0:
			return "";		
		/* Larger than base unit */
		case 1:
			return "deca";
		case 2:
			return "hecto";
		case 3:
			return "kilo";
		case 6:
			return "mega";
		case 9:
			return "giga";
		case 12:
			return "tera";
		case 15:
			return "peta";
		case 18:
			return "exa";
		case 21:
			return "zetta";
		case 24:
			return "yotta";
		default:
			return "(N/A)";
	}
}

/* ***MASS*** */

Mass::Mass()
{
	value = 0;
	unit = 0;
	unit_suffix = "gram";
	plural_unit_suffix = "grams";
}

Mass::~Mass()
{
}

std::string Mass::makeString()
{
	std::string result; //This string holds the result.

	//String returned format:
	//<value> <unit prefix><unit sufix>

	result = mstring::toString(value); //Convert the value.
	if(getUnitPrefix(unit) == "(N/A)")
	{
		//Use " x 10^zerocount" instead.

		result += "×10^";
		result += mstring::toString(unit);
		result += " ";
	}
	else
	{
		result += " "; //Add a space, for formatting purposes.
		result += getUnitPrefix(unit); //Add the unit prefix.
	}
	result += getUnitName(); //Add the unit name. Use this function to automatically solve the problem of plural or singular.

	return result; //Return the thing.
}

std::string Mass::getUnitName()
{
	return ((value == 1) ? unit_suffix : plural_unit_suffix);
}

void Mass::set(double _value, long _unit)
{
	value = _value;
	unit = _unit;
}

/* ***CHARGE*** */

Charge::Charge()
{
	value = 0;
	unit = 0;
	unit_suffix = "coulomb";
	plural_unit_suffix = "coulombs";
}

Charge::~Charge()
{
}

std::string Charge::makeString()
{
	std::string result; //The result is stored here.

	//Check Mass::makeString for the format of the returned string.

	result = mstring::toString(value); //Convert the value.
	if(getUnitPrefix(unit) == "(N/A)")
	{
		//Use " x 10^zerocount" instead.

		result += "×10^";
		result += mstring::toString(unit);
		result += " ";
	}
	else
	{
		result += " "; //Add a space, for formatting purposes.
		result += getUnitPrefix(unit); //Add the unit prefix.
	}
	result += getUnitName(); //Add the unit name. Use this function to automatically solve the problem of plural or singular.

	return result; //Return it.
}

std::string Charge::getUnitName()
{
	return ((value == 1) ? unit_suffix : plural_unit_suffix);
}

void Charge::set(double _value, long _unit)
{
	value = _value;
	unit = _unit;
}

/* ***Distance*** */

Distance::Distance()
{
	value = 0;
	unit = 0;
	unit_suffix = "meter";
	plural_unit_suffix = "meters";
}

Distance::~Distance()
{
}

std::string Distance::makeString()
{
	std::string result; //The result is stored here, uh huh.

	result = mstring::toString(value); //Convert the value.
	if(getUnitPrefix(unit) == "(N/A)")
	{
		//Use " x 10^zerocount" instead.

		result += "×10^";
		result += mstring::toString(unit); //Add the zerocount now.
		result += " "; //Add space, for formatting purposes.
	}
	else
	{
		result += " "; //Add a space, for formatting purposes.
		result += getUnitPrefix(unit); //Add the unit prefix.
	}

	result += getUnitName(); //Add the unit name. Use this function to automatically solve the problem of plural or singular.

	return result; //Return the end result.
}

std::string Distance::getUnitName()
{
	return ((value == 1) ? unit_suffix : plural_unit_suffix);
}

void Distance::set(double _value, long _unit)
{
	value = _value;
	unit = _unit;
}

Distance parsecsToMeters(Distance input)
{
	return input; //For now, just return input to eliminate warning. TODO: Do the conversion.
}

Distance MetersToParsecs(Distance input)
{
	return input; //For now, just return input to eliminate warning. TODO: Do the conversion.
}

} //namespace ws
