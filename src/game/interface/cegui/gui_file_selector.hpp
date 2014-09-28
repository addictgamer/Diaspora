/* Copyright Ciprian Ilies */

#pragma once

#include <CEGUI/CEGUI.h>
//#include "disk_object.hpp"
#include <GEngine/GEngine.hpp>

namespace gnomal
{

class Interface;

//TODO: File and folder selector support.
/*
 * TODO: This needs to be rewritten to support:
 * * Typing in the file/folderpath
 * * Forward and backwards buttons?
 */
class GUIFileSelector
{
private:
	virtual bool handleClick(const CEGUI::EventArgs& e);
	virtual void wireEvents();
	void updateFolderList();

	CEGUI::Window* frame;

	std::string selection_result;
	std::string d_fileFilter;
	std::vector<std::string> item_list;

	//Path to the current directory.
	std::string current_directory;

	//Reference to the GUI context this is working with.
	CEGUI::GUIContext &context;

	//Reference to the interface this is part of.
	Interface &interface;

	CEGUI::Window *root;

	//void (*callback)();
	//std::function<void()> close_callback;

	bool hidden;
public:
	//GUIFileSelector(CEGUI::GUIContext&, Interface&, void (*close_callback)());
	//GUIFileSelector(CEGUI::GUIContext&, Interface&, std::function<void()> );
	GUIFileSelector(CEGUI::GUIContext&, Interface&);
	~GUIFileSelector(); //Do not use this. Use the hide() function.

	/*
	 * Makes the Folder selector appear in CEGUI::Window
	 */
	void show(CEGUI::Window *the_root);

	/*
	 * Hides the folder selector.
	 */
	void hide();

	/*
	 * Returns the last selected file.
	 */
	std::string getResult();

	/**
		@short set the current folder
	*/
	void setFolder(std::string);

	/**
		@short sets the filter string. The string will be used to enable/disable OK button when files in the current
			folder matches the filter string (i.e., "*.jpg" string will enable OK button only when the current folder
			contains files with extension .jpg). By default is "*", showing all files.
	*/
	void setFileFiler(std::string s){d_fileFilter = s;}

	//void (*closeCallback)(Interface *interface);
	void (*closeCallback)(Interface *, std::string);
};

} //namespace gnomal
