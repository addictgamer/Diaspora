/* Copyright Ciprian Ilies */

#include "entity.hpp"

#include "../space/space.hpp"

namespace ws
{

Entity::Entity()
{
	container_space = nullptr;
	composition_space = nullptr;

	//----------GAME SPECIFIC CODE BELOW----------
	sprite = nullptr;
}

Entity::~Entity()
{
	container_space = nullptr;
	composition_space = nullptr; //Might delete this later. We'll see. I really don't like this variable. And I forgot what I wanted to do with this. Heh. I blame...something. Why didn't I write it down?

	//----------GAME SPECIFIC CODE BELOW----------
	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void Entity::setContainerSpace(Space &space)
{
	if (container_space)
	{
		//TODO: Handle multi-tile entities.
		container_space->removeEntity(this);
	}
	container_space = &space;
	container_space->addEntity(this); //Tell the container space a new entity just entered it.
}

//----------GAME SPECIFIC CODE BELOW-----
void Entity::render(GEngine::mgfx::d2d::D2D &d2d, int X, int Y)
{
	if (sprite)
	{
		sprite->draw(d2d, X, Y);
	}
}

} //namespace ws
