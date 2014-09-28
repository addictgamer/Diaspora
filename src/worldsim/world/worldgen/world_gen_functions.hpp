/* Copyright Ciprian Ilies */

/*
This file contains functions that generate stuff, such as the planets, asteroids...stars...etc.
*/

#pragma once

#include "../../internal_header.hpp"
#include <vector>
#include <string>

namespace ws
{

class World; //Forward declaration of this.

bool genAsteroid(World &world, std::vector<std::string> parameters); //Generate an asteroid.

bool genFlatworld(World &world, std::vector<std::string> parameters); //Generate an infinite flat world.

} //namespace ws
