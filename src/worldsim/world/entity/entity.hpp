/* Copyright Ciprian Ilies */

#pragma once

#include "../../internal_header.hpp"

#include <GEngine/GEngine.hpp>

namespace ws
{

class Space;

class Entity
{
public:
	Space *container_space; //The space this entity occupies.
	Space *composition_space; //The space that composes this entity. //TODO: I wanted to do something else here, but what? Sadly, I forget. Why did I not write it down? Or did I, but I just can't find the page? We'll have to see.

	Entity();
	~Entity();

	void setContainerSpace(Space &space);

	//----------GAME SPECIFIC CODE BELOW----------
	GEngine::mgfx::d2d::Sprite *sprite;
	//Render the entity.
	void render(GEngine::mgfx::d2d::D2D &d2d, int X, int Y);
};

} //namespace ws
