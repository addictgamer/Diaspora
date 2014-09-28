/* Copyright Ciprian Ilies */

#include "worldsim.hpp"

namespace gnomal
{

namespace world_stuff
{

SpriteResource::SpriteResource()
{
	filepath = "";
	sprite = nullptr;
	id = 0;
}

SpriteResource::SpriteResource(std::string filepath, unsigned long id) :  filepath(filepath), id(id)
{
	//std::cout << "SpriteResource() filepath = \"" << filepath << "\"\n";
	sprite = new GEngine::mgfx::d2d::Sprite;
	if(!sprite->loadFromFile(filepath))
	{
		std::cout << "Error: Failed to load SpriteResource.\n";
		throw; //TODO: Error. It failed to load the sprite. Do something good for an error here, I guess.
	}
}

SpriteResource::~SpriteResource()
{
	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}
}

SpriteResourceManager::SpriteResourceManager()
{
}

SpriteResourceManager::~SpriteResourceManager()
{
	std::vector<SpriteResource* >::iterator iter;
	for (iter = resources.begin(); iter != resources.end(); ++iter)
	{
		if ((*iter))
		{
			delete (*iter);
		}
		//resources.erase(iter);
	}
}

unsigned long SpriteResourceManager::addResource(std::string filepath)
{
	unsigned long id = getUnusedID();
	SpriteResource *resource = new SpriteResource(filepath, id);
	resources.push_back(resource);
	return id;
}

GEngine::mgfx::d2d::Sprite* SpriteResourceManager::getSprite(unsigned long id) //Returns the sprite of the resource with the specified id.
{
	std::vector<SpriteResource* >::iterator iter;
	for (iter = resources.begin(); iter != resources.end(); ++iter)
	{
		if ((*iter)->id == id)
		{
			return (*iter)->sprite; //Found the SpriteResource matching the given id. Return its sprite.
		}
	}

	return nullptr;
}

unsigned long SpriteResourceManager::getUnusedID()
{
	return resources.size(); //TODO: Temporary hack. When resizable SpriteResource blargs are created, modify this to account for that.
}

} //namespace world_stuff

} //namespace gnomal
