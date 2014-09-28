/* Copyright Ciprian Ilies */

#include <iostream>

#include "../../worldsim/worldsim.hpp"

#include "worldsim.hpp"

#include "../interface/interface.hpp"

namespace gnomal
{

World::World()
{
	world = nullptr;
	tiles = nullptr;
	camera = nullptr;
	space_no_sprite_sprite = nullptr;
	camera_sprite = nullptr;
}

World::~World()
{
	if (world)
	{
		delete world;
		world = nullptr;
	}

	if (tiles)
	{
		delete tiles;
		tiles = nullptr;
	}

	if (camera)
	{
		delete camera;
	}

	if (space_no_sprite_sprite)
	{
		delete space_no_sprite_sprite;
		space_no_sprite_sprite = nullptr;
	}

	if (camera_sprite)
	{
		delete camera_sprite;
		camera_sprite = nullptr;
	}
}

bool World::genTestworld(GEngine::mgfx::d2d::D2D &d2d)
{
	if (!genFlatworld(world)) //Generate new world, with error checking.
	{
		std::cout << "Error: Failed to generate new world.\n";
		return false; //TODO: Proper error handling.
	}

	//TODO: Create the camera too.

	if (world)
	{
		if (world->existence && world->existence->universes[0] && world->existence->universes[0]->dimensions)
		{
			ws::Dimension *dimension = world->existence->universes[0]->dimensions;
			if (dimension->space)
			{
				ws::Space *current_space = dimension->space;

				ws::Space *camera_parent_space = current_space->getChild((ws::SPACE_SIZE / 2), (ws::SPACE_SIZE / 2), (ws::SPACE_SIZE / 2));

				if (camera)
				{
					delete camera; //Delete the camera if it exists. It shouldn't exist, though.
				}
				camera = new ws::Entity; //Allocate memory for the camera.

				camera->setContainerSpace(*camera_parent_space);
				camera->sprite = new GEngine::mgfx::d2d::Sprite;
				if (!camera->sprite->loadFromFile(CAMERA_SPRITE_FILEPATH)) //Load the sprite, with error checking.
				{
					//TODO: Proper error handling.
					std::cout << "ERROR: Failed to load camera_sprite. Aborting World::genTestWorld().\n";
					return false; //Error.
				}
				camera->sprite->d2d = &d2d;
			}
		}
	}

	if (!space_no_sprite_sprite) //Load this if it doesn't exist.
	{
		space_no_sprite_sprite = new GEngine::mgfx::d2d::Sprite;

		if (!space_no_sprite_sprite->loadFromFile(SPACE_NOSPRITE_SPRITE_FILEPATH)) //Load the sprite, with error checking.
		{
			//TODO: Proper error handling.
			std::cout << "ERROR: Failed to load space_no_sprite_sprite. Aborting World::getTestWorld().\n";
			return false; //Error.
		}
		space_no_sprite_sprite->d2d = &d2d;
		space_no_sprite_sprite->setLoc(704, 300);
	}

	return true; //Success by default.
}

void World::render(GEngine::mgfx::d2d::D2D &d2d, sf::Font &font)
{
	//TODO: Render it.
	/*
	//Old WIP code, probably no longer needed since I like the new method better.
	if (world) //We need the world to continue.
	{
		if (world->existence && world->existence->universes[0] && world->existence->universes[0]->dimensions) //We need all of these to exist to continue.
		{
			ws::Dimension *dimension = world->existence->universes[0]->dimensions; //Point to this so we save a lot of typing.
			if (dimension->space) //We can't continue without space.
			{
				ws::Space *current_space = dimension->space;
			}
		}
	}*/

	/*
	 * I think that I can just use the camera to render everything, so scratch the above code. I take the camera and spread out to the surrounding space to draw everything.
	 */
	if (world && camera)
	{
		if (world->existence && world->existence->universes[0] && world->existence->universes[0]->dimensions) //We need all of these to exist to continue.
		{
			if (camera->container_space)
			{
				/*
				 * Right, so the plan is as follows:
				 *	Take the camera entity's container space, set it as a centerpoint, and calculate how many spaces would fit onscreen at once based on a variable serving the purpose of space_sprite_size.
				 *	From there, build a 2 dimensional array (via a std::vector) of spaces with the camera entity at its centerpoint and all the spaces on the same layer.
				 *	From there, call the render function of all of those spaces. OR: Every time the camera moves, dynamically update a vector of all visible spaces.
				 *	The latter method would probably be more efficient in the long run.
				 *
				 * TODO: At some future point, this needs to be modified to look at the space on other layers and take them into account too.
				 * Additionally:
				 *	* Change the camera entity to be wrapped by a camera class. Perhaps via creating a child class of the Entity class and building it right into the worldsim?
				 *	* Change this to allow looking from either the eyes of an entity in the world & the current top-down GM/"god" view.
				 */

				ws::Space *centerpoint = camera->container_space; //This will act as the center of the draw rectangle.
				if (!centerpoint || !camera->container_space)
				{
					std::cout << "ERROR: Camera doesn't exist in space. Can't render! Aborting.\n";
					return;
				}

				/*
				 * Right, now how do I grab the spaces around it...Idea:
				 *
				 * - - - - -
				 * - - - - -
				 * - - + - -
				 * - - - - -
				 * - - - - -
				 *
				 * So, seen in the example:
				 *	- = a space
				 *	+ = ws::Space* centerpoint (declared above).
				 *
				 * So what I'm going to do is take the center space, and do a while current_space = <direction>_neighbor, current_space = <direction>_neighbor until reached either last existing space or the number of spaces on screen from the center to one edge of the screen.
				 * Doing that, I will end up with:
				 *
				 * - - | - -
				 * - - - - -
				 * | - + - |
				 * - - - - -
				 * - - | - -
				 *
				 * So, Seen in the example:
				 *	- = a space
				 *	+ = ws::Space* centerpoint (declared above).
				 *	| = edge of draw rectangle.
				 * ...
				 * ...
				 * ...
				 * Actually, scratch that idea, I got a better one:
				 *	Take centerspace, loop up until edge of screen or last space reached. Then loop left until edge of screen or last space reached.
				 *	Then loop column by column until every space is rendered.
				 * I'll need to account for space not existing in this method...That might be resolved with adding an overlay that keeps track if the space was rendered.
				 * As every space is rendered, it checks its neighbors to see if they are:
				 *	* Onscreen.
				 *	* To the left (not going to be rendered next because it renders from left to right).
				 *	* The current render column is the first one (because otherwise all spaces would be rendered).
				 * If it finds any space there, it adds it to the list of those to be rendered.
				 * Then it renders all of those spaces.
				 *
				 * Some issues I see with this method:
				 *	* There will be regions of space not rendered because they are still onscreen but not linked to any existing tile.
				 *	* This method is not future-proof. It's only temporary. It doesn't even consider the other layers!
				 */

				//For now, let's do the laziest and most temporary method. Loop up then left, draw all columns. Don't even consider the possibility of other tiles outside of this rectangle.
				{

					//First calculate how many spaces will fit on screen (TODO: should probably put this in its own function or something of that ilk. Maybe only calculate it at the beginning and whenever the screen is resized?):
					int h = d2d.window->getHeight() - interface.getGameviewY();
					int w = d2d.window->getWidth() - interface.getGameviewRightedge();
					int num_horizontal = ceil((float)w / (float)SPACE_SPRITE_DIMENSION);
					int num_horizontal_original = num_horizontal; //Preserve this for use later in determining draw coordinates.
					int num_vertical = ceil((float)h / (float)SPACE_SPRITE_DIMENSION);
					int num_vertical_original = num_vertical; //Preserve this for use later in determining draw coordinates.
					//std::cout << "Num horizontal: " << num_horizontal << " & num_vertical: " << num_vertical << " & number on screen at once: " << num_horizontal * num_vertical << "\n";
					//if (w / SPACE_SPRITE_DIMENSION > )

					ws::Space *current = centerpoint; //The starting point.
					{
						bool done = false; //Controls the while loop below.
						int num_went_up = 0; //How many it's gone up.
						int target_num_up = num_vertical / 2; //How many its supposed to go up.
						//std::cout << "target_num_up = " << target_num_up << "\n";
						while (!done)
						{
							if (num_went_up == target_num_up) //Reached our target destination.
							{
								done = true; //Done.
								//std::cout << "Reached target destination.\n";
							}
							else
							{
								if (!current->up()) //Reached the end of the line.
								{
									done = true; //Done.
									//std::cout << "Reached end of the line.\n";
								}
								else
								{
									//We're not done yet! Move up one more.
									current = current->up(); //This actually goes up one more.
									num_went_up++; //Increment this.
									//std::cout << "We're moving on up.\n";
								}
							}
						}
						//std::cout << "num_went_up = " << num_went_up << "\n";
						num_vertical -= (target_num_up - num_went_up); //Offset this so it doesn't render a bunch of stuff offscreen.
					}
					//Great, now take that result and move left of it to our next target destination.
					{
						bool done = false; //Controls the while loop below.
						int num_went_left = 0; //How many it's gone left.
						int target_num_left = num_horizontal / 2; //How many its supposed to go left.
						//std::cout << "target_num_left = " << target_num_left << "\n";
						while (!done)
						{
							if (num_went_left == target_num_left)
							{
								done = true;
								//std::cout << "Reached target destination.\n";
							}
							else
							{
								if (!current->left())
								{
									done = true;
									//std::cout << "Reached end of the line.\n";
								}
								else
								{
									//We're not done yet. Move left one more.
									current = current->left(); //This actually moves to the next space.
									num_went_left++;
									//std::cout << "Moving left.\n";
								}
							}
						}
						//std::cout << "num_went_left = " << num_went_left << "\n";
						num_horizontal -= (target_num_left - num_went_left); //Offset this so it doesn't render a bunch of stuff offscreen.
					}

					//Calculate draw offset.
					int draw_offset_x = num_horizontal_original - num_horizontal;
					//std::cout << "draw_offset_x = " << draw_offset_x << "\n";
					//int draw_offset_y = interface.getGameviewY() + (num_vertical_original - num_vertical);
					int draw_offset_y = num_vertical_original - num_vertical;
					//std::cout << "draw_offset_y = " << draw_offset_y << "\n";

					//Great, now actually render everything.
					//ws::Space *top_left = current;
					{
						//ws::Space start_of_row = current; //Unnecessary.
						ws::Space *start_of_column = current;
						for (int x = 0; x < num_horizontal; ++x)
						{
							//std::cout << "x = " << x << ". num_horizontal = " << num_horizontal << "\n";
							for (int y = 0; y < num_vertical; ++y)
							{
								int draw_x = (x + draw_offset_x) * SPACE_SPRITE_DIMENSION;
								//std::cout << "draw_x = " << draw_x << "\n";
								int draw_y = interface.getGameviewY() + ((y + draw_offset_y) * SPACE_SPRITE_DIMENSION);
								//std::cout << "draw_y = " << draw_y << "\n";
								current->render(d2d, draw_x, draw_y, space_no_sprite_sprite, font, SPACE_SPRITE_DIMENSION, SPACE_SPRITE_DIMENSION); //Render the current space.
								//std::cout << "RENDERING (x,y): (" << x << ", " << y << ").\n";

								if (current->down()) //Move on to the next space, if possible.
								{
									current = current->down();
								}
								else
								{
									y = num_vertical; //Hit last space. Done with this column.
								}
							}
							if (start_of_column->right()) //Move to the next column, if possible.
							{
								//std::cout << "Rendering to the right next.\n";
								current = start_of_column->right();
								start_of_column = current; //Move the start of the column to the current space to keep up.
							}
							else
							{
								//No more spaces (and thus no more columns) in this row. Done rendering!
								//std::cout << "Rendered last column.\n";
								x = num_horizontal;
							}
						}
					}
					//std::cout << "***END RENDER***\n\n";
				}
			}
		}
	}
}

ws::Space* World::getSpaceAtCoordinates(GEngine::mgfx::d2d::D2D &d2d, int x, int y)
{
	if (world && camera)
	{
		if (world->existence && world->existence->universes[0] && world->existence->universes[0]->dimensions) //We need all of these to exist to continue.
		{
			if (camera->container_space)
			{
				//Grab the width and height of the window.
				int h = d2d.window->getHeight() - interface.getGameviewY();
				int w = d2d.window->getWidth() - interface.getGameviewRightedge();
				if (x > w || x < 0 || y > h || y < 0)
					return nullptr;
				//Calculate how many spaces fit horizontally and vertically.
				int num_horizontal = ceil((float)w / (float)SPACE_SPRITE_DIMENSION);
				int num_vertical = ceil((float)h / (float)SPACE_SPRITE_DIMENSION);

				//Calculate the x and y (in spaces, not pixels) of the target space (the space that was clicked on, or rather, the space at the specified pixel coordinates).
				int target_space_x = x / SPACE_SPRITE_DIMENSION;
				int target_space_y = y / SPACE_SPRITE_DIMENSION;

				//Calculate the camera's space's x & y (in spaces, not pixels).
				int camera_space_x = ceil(num_horizontal / 2);
				int camera_space_y = ceil(num_vertical / 2);
				//Calculate the target space's relative position to the camera's space's coordinates (in spaces, not coordinates).
				int x_dif = (camera_space_x - target_space_x);
				int y_dif = (camera_space_y - target_space_y);

				//Return the space at the specified coordinates (coordinates are in spaces, not pixels).
				return camera->container_space->parent_space->getChild((camera->container_space->x - x_dif), (camera->container_space->y - y_dif), camera->container_space->z);
			}
		}
	}

	return nullptr;
}

void World::moveCamera(int x, int y, int z)
{
	ws::Space *target_space = camera->container_space->parent_space->getChild((camera->container_space->x + x), (camera->container_space->y + y), (camera->container_space->z + z)); //Grab the target space.

	camera->setContainerSpace(*target_space); //Set the camera at the target space.
}

} //namespace gnomal
