/* Copyright Ciprian Ilies */

/*
This is where the front end interfaces with the worldsim module.

Contains such things as the world definition.
*/

#pragma once

#include "../../worldsim/worldsim.hpp"

#include <GEngine/GEngine.hpp>

namespace ws
{

class Space;

}

namespace gnomal
{

//TODO: These defines are only temporary until I implement loading stuff from configuration files.
#define SPACE_SPRITE_DIMENSION 64
#define SPACE_NOSPRITE_SPRITE_FILEPATH "data/gfx/space-nosprite.png"
#define CAMERA_SPRITE_FILEPATH "data/gfx/camera.png"

namespace world_stuff
{

//TODO: Implement.
class SpriteResource
{
public:
	std::string filepath;
	GEngine::mgfx::d2d::Sprite *sprite;
	unsigned long id; //Must be unique.

	SpriteResource();
	SpriteResource(std::string filepath, unsigned long id);
	~SpriteResource();
};

class SpriteResourceManager
{
public:
	std::vector<SpriteResource* > resources; //TODO: Maybe a map instead of vector? To bind resources to their id.

	SpriteResourceManager();
	~SpriteResourceManager();

	unsigned long addResource(std::string filepath); //Creates a sprite from the given filepath. Returns the ID of the new sprite.
	GEngine::mgfx::d2d::Sprite* getSprite(unsigned long id); //Returns the sprite of the resource with the specified id.
	unsigned long getUnusedID(); //Returns the first unused id it can find. //TODO: Temporary hack. When resizable SpriteResource blargs are created, modify this to account for that.
};

} //namespace world_stuff

/*
 * Basically a wrapper for space.
 * I'd like to use this instead of directly accessing the space, but I don't know how to make it efficient (I have to assign the pointers and whatnot...).
 * The main benefit I see in this is seperating the worldsim code from the game implementation, such as adding the sprite here instead of in the worldsim code.
 * One way of working around this is giving each space a "gamedata" pointer thingy and using that.
 * For now, I might just not actually use this.
 */
class Tile
{
private:
	ws::Space *space;
public:
	Tile();
	~Tile();
};


//Wrapper to the worldsim world class.
class World
{
private:
	Tile *tiles; //The tiles!

	/*
	 * The 'eye' we're going to use to view the world.
	 *
	 * For now, it's just going to keep track of what space it's on and from there, it's going to render all space on the same level. We'll also use it to figure out where a mouseclick takes place.
	 * The eye is in the center of the screen. It moves around with the camera, and the game renders all the space around it until the edge of the screen is hit.
	 */

	GEngine::mgfx::d2d::Sprite *space_no_sprite_sprite; //The sprite drawn when a space doesn't have its own sprite.
	GEngine::mgfx::d2d::Sprite *camera_sprite; //The camera entity's sprite.
public:
	ws::World *world; //Pointer to the actual world.
	ws::Entity *camera; //The "eye" we're going to use to view the world. //TODO: At some point, turn this into a built-in child of the entity class in the worldsim library.

	world_stuff::SpriteResourceManager sprite_resource_manager; //This thing is there to serve sprites to tiles, to be as memory efficient as possible. Only the least number of sprites required exist at any one point in time.

	World();
	~World();

	bool genTestworld(GEngine::mgfx::d2d::D2D &d2d); //Generates a test world.

	void render(GEngine::mgfx::d2d::D2D &d2d, sf::Font &font); //Render the world.

	/*
	 * Returns a pointer to the tile at the specified coordinates (coordinates are in pixels).
	 * Intended to be used for when the game needs to know where in the game world the user's click is.
	 */
	ws::Space* getSpaceAtCoordinates(GEngine::mgfx::d2d::D2D &d2d, int x, int y);

	void moveCamera(int x, int y, int z);
};

} //namespace gnomal
