/* Copyright Ciprian Ilies */

#include <iostream>

#include "interface.hpp"

#include <GEngine/graphic/2d/2d.hpp>
#include <GEngine/interface/interface.hpp>

#include "../worldsim/worldsim.hpp"

#include "../game.hpp"

namespace gnomal
{

//#define GAMEVIEW_Y 30
#define GAMEVIEW_Y 0
//#define GAMEVIEW_RIGHTEDGE 200
#define GAMEVIEW_RIGHTEDGE 0

std::string GUI_LAYOUT_MAINMENU = "diaspora-mainmenu.layout";
//std::string GUI_LAYOUT_FILE_SELECTOR = "file_selector.layout";

using namespace GEngine;

Interface::Interface()
{
	active_window = nullptr;

	main_menu = nullptr;
}

Interface::~Interface()
{
	if (interface)
		delete interface;
}

bool Interface::initialize(mgfx::d2d::D2D &_d2d, int window_width, int window_height, bool fullscreen, std::string windowname)
{
	main_window.create(window_width, window_height, fullscreen, windowname, true);
	main_window.setFramerateLimit(30); //Limit the FPS...

	//TODO: Make a function to handle this.
	_d2d.window = &main_window; //Point this accordingly.
	main_window.parent_d2d = &_d2d; //And point right back at it.

	interface = new mui::Interface; //Allocate memory for the interface.

	if (!interface->loadFont(MAIN_FONT_FILEPATH)) //Load the interface's font, with error handling.
	{
		std::cout << "Error: Failed to load interface's font.\n";
		return false;
	}

	std::vector<std::string> cegui_schemes;
	cegui_schemes.push_back(DEFAULT_CEGUI_SCHEME); //TODO: Load schemes from config files.
	if (!interface->initialize(_d2d, cegui_schemes)) //Initialize the interface, with error checking.
	{
		std::cout << "ERROR: Failed to initialize game/interface's mui::interface (the engine's interface module).\n";
		return false;
	}

	//Load all from the xml layout.
	main_menu = interface->createVirtualWindowFromLayout(GUI_LAYOUT_MAINMENU);
	interface->setRootWindow(main_menu, _d2d);
	setActiveWindow(*main_menu); //Set the active window to the main menu.

	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("TaharezLook/Tooltip"); //TODO: Set in XML, if possible.

	//Load the titlescreen's sprite.
	titlescreen_background_sprite = std::shared_ptr<mgfx::d2d::Sprite>(new mgfx::d2d::Sprite);
	if(!titlescreen_background_sprite->loadFromFile(TITLESCREEN_BACKGROUND_SPRITE_PATH))
	{
		std::cout << "Error: Failed to load titlescreen_background_sprite.\n";
		return false;
	}
	titlescreen_background_sprite->d2d = &_d2d;
	titlescreen_background_sprite->sety(getGameviewY());

	return true; //Success.
}

void Interface::update()
{
	if (interface) //Can't continue without this. But...shouldn't it exist at all times anyway?
	{
		interface->update(); //Update the interface.

		/*if (interface->windows.size()) //Interface needs to have a d2d.
		{
			if (interface->windows[0]->window)
			{
				//TODO: Check events.
				std::vector<sf::Event>::iterator iter = interface->windows[0]->window->events.begin();
				for (; iter != interface->windows[0]->window->events.end(); ++iter) //Loop through all the events.
				{
					//TODO: Check if the event is a mouseclick.
					switch ((*iter).type)
					{
						case sf::Event::MouseButtonPressed:
							if ((*iter).mouseButton.button == sf::Mouse::Left)
							{
								//TODO: Do a check to make sure no interface element was clicked.
								if (game.world)
								{
									//TODO: Do something with it.
									ws::Space *the_space = game.world->getSpaceAtCoordinates(*interface->windows[0], (*iter).mouseButton.x, (*iter).mouseButton.y);
									if (the_space)
									{
										std::cout << "Space (" << the_space->x << ", " << the_space->y << ", " << the_space->z << ") clicked\n";
									}
									else
									{
										std::cout << "Error: No space exists where you clicked.\n";
									}
								}
							}
							break;
						default:
							break;
					}
				}
			}
		}*/
	}

	//Exception checking because it's needed if getChild("CreateWorld") fails because there is no such child.
	try
	{
		//If the world exists, and the resource browser does not exist, and the cegui window exists, and the create world button exists (wouldn't exist if the current interface isn't the gm view one anymore), and the create world button is not visible...
		/*if (game.world && !resource_browser_window && interface->getRootWindow(*interface->windows[0]) && interface->getRootWindow(*interface->windows[0])->getChild("Menubar/CreateWorld") && !interface->getRootWindow(*interface->windows[0])->getChild("Menubar/CreateWorld")->isEnabled())
		{
			//Create the resource browser window.

			resource_browser_window = new GEngine::mgfx::d2d::D2D;
			//Setup the d2d, with error checking.
			if (!resource_browser_window->setup())
			{
				std::cout << "Error: Failed to set up resource_browser_window.\n";
				throw;
			}

			GEngine::mgfx::Window *resource_browser_window_window = new mgfx::Window;
			resource_browser_window_window->create(WINDOWWIDTH, WINDOWHEIGHT, FULLSCREEN, "Resource Browser", true); //TODO: Other dimensions here.
			resource_browser_window_window->can_close = false;

			//TODO: Make a function for this.
			resource_browser_window->window = resource_browser_window_window; //Point this accordingly.
			resource_browser_window->window->parent_d2d = resource_browser_window; //Point right back at it.

			//resource_browser_window_cegui_renderer = &CEGUI::OpenGLRenderer::create();
			//resource_browser_window_cegui_context = &CEGUI::System::getSingleton().createGUIContext(resource_browser_window_cegui_renderer->getDefaultRenderTarget()); //Create a cegui context for the resource browser window.
			resource_browser_interface = interface->createVirtualWindowFromLayout(GUI_LAYOUT_RESOURCE_BROWSER); //TODO: Uncomment when you figure out how to make CEGUI properly draw to multiple SFML windows.
			interface->addD2D(*resource_browser_window);
			resource_browser_window->cegui_gui_context->setRootWindow(resource_browser_interface); //TODO: Uncomment when you figure out how to make CEGUI properly draw to multiple SFML windows.
		}*/ //TODO: Uncomment this if I decide to put the resource stuff in a seperate window.
	}
	catch (...)
	{
	}
}

void Interface::drawLevelOne()
{
	if (gamestate == GAMESTATE_TITLE)
	{
		if (titlescreen_background_sprite) //If the titlescreen background sprite exists.
		{
			titlescreen_background_sprite->sprite->setScale((float)((float)(interface->windows[0]->window->getWidth() - getGameviewRightedge()) / (float)titlescreen_background_sprite->getWidth()), (float)((float)(interface->windows[0]->window->getHeight() - getGameviewY()) / (float)titlescreen_background_sprite->getHeight()));
			titlescreen_background_sprite->draw(); //Draw the titlescreen's background sprite.
		}
	}
}

void Interface::drawLevelTwo()
{
}

void Interface::drawLevelThree()
{
	interface->draw(); //Draw the interface.
}

void Interface::windowDraw()
{
	main_window.draw(); //Draw the window.
}

void Interface::windowUpdate()
{
	main_window.update(); //Update the window.

	if (main_window.closed) //Check if the window was closed.
	{
			game.quit = true;
	}
}

int Interface::getGameviewY()
{
	return GAMEVIEW_Y;
}

int Interface::getGameviewRightedge()
{
	int retval = 0;

	if (gamestate == GAMESTATE_INGAME)
	{
		//TODO: Move into VTT Module.
		/*if (interface->getRootWindow(*interface->windows[0])->getChild("RightSidebar")->isVisible())
		{
			retval = GAMEVIEW_RIGHTEDGE; //TODO: Make it blarg the width of the sidebar.
		}*/
	}
	return retval;
}

void Interface::setActiveWindow(CEGUI::Window &window)
{
	active_window = &window;
}

Interface interface;

} //namespace gnomal
