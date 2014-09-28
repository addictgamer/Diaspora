/* Copyright Ciprian Ilies */

#pragma once

#include <CEGUI/CEGUI.h>
#include <GEngine/GEngine.hpp>

namespace gnomal
{

class Interface;

class GUIGameSelector
{
private:
	virtual bool handleClick(const CEGUI::EventArgs& e);
	virtual void wireEvents();
	void updateGameList(std::string directory);
	void validateGames(std::string directory);

	CEGUI::Window* frame;

	std::string selection_result;
	std::string d_fileFilter;
	std::vector<std::string> item_list;

	//Reference to the GUI context this is working with.
	CEGUI::GUIContext &context;

	//Reference to the interface this is part of.
	Interface &interface;

	CEGUI::Window *root;

	bool hidden;
public:
	GUIGameSelector(CEGUI::GUIContext&, Interface&);
	~GUIGameSelector(); //Do not use this. Use the hide() function.

	/*
	 * Makes the Folder selector appear in CEGUI::Window
	 */
	void show(CEGUI::Window *the_root, std::string directory);

	/*
	 * Hides the folder selector.
	 */
	void hide();

	/*
	 * Returns the last selected file.
	 */
	std::string getResult();

	//void (*closeCallback)(Interface *interface);
	void (*closeCallback)(Interface *, std::string);
};

} //namespace gnomal
