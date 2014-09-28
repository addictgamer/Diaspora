/* Copyright Ciprian Ilies */

#pragma once

#include <memory>

#include <GEngine/GEngine.hpp>

namespace gnomal
{

//TODO: Stuff like "ifdef GEngine_interal"
//using namespace GEngine;

//These are only temporary until I load stuff like these from the cfg.
//Background sprites:
#define TITLESCREEN_BACKGROUND_SPRITE_PATH "data/interface/title/titlescreen.png"
//CEGUI defines:
extern std::string GUI_LAYOUT_MAINMENU;//= "gnomal-mainmenu.layout";
//extern std::string GUI_LAYOUT_FILE_SELECTOR;//= "file_selector.layout";
#define DEFAULT_CEGUI_SCHEME "TaharezLook"
//#define DEFAULT_CEGUI_SCHEME "VanillaSkin"
//Font filepaths
#define MAIN_FONT_FILEPATH "data/interface/cegui/fonts/DejaVuSans.ttf"

class Interface //The big wrapper over the interface stuff.
{
private:
	//--------Titlescreen variables-------
	std::shared_ptr<GEngine::mgfx::d2d::Sprite> titlescreen_background_sprite; //Titlescreen background sprite.

	//--------Other stuff--------
	//CEGUI windows (for interface 'pages' -- eg main menu, lobby, ingame, etc.)
	//TODO: Hide all this in GEngine and create some wrapper for it.

	CEGUI::Window *main_menu; //The root window for the main menu.
public:
	GEngine::mui::Interface *interface; //Links and wraps the engine's interface.

	GEngine::mgfx::Window main_window; //The main window.
	CEGUI::Window *active_window; //The window that is currently serving as CEGUI's root.

	Interface(); //Constructor.
	~Interface(); //Deconstructor.

	bool initialize(GEngine::mgfx::d2d::D2D &_d2d, int window_width, int window_height, bool fullscreen, std::string windowname); //Initialize the interface.

	void update(); //Updates the interface.

	void drawLevelOne(); //First draw level. Things here are drawn first, behind everything else.
	void drawLevelTwo(); //Second draw level. It's actually the third compared to the rest of the game, but regardless, it's the second of this function. Everything here is drawn after the "inworld stuff" has been drawn.
	void drawLevelThree(); //The third draw level. It's the last draw level of the entire game. Everything here is drawn over EVERYTHING.

	/*
	 * Updates all of the windows.
	 */
	void windowUpdate();

	/*
	 * Draws all of the windows.
	 */
	void windowDraw();

	//--------Button click callbacks until I figure out CEGUI more--------

	/*
	 * Returns the Y that the game view starts at.
	 */
	int getGameviewY();

	/*
	 * Returns the X that the game view ends at.
	 */
	int getGameviewRightedge();

	/*
	 * Sets the active virtual window.
	 */
	void setActiveWindow(CEGUI::Window &window);
};

extern Interface interface;

} //namespace gnomal
