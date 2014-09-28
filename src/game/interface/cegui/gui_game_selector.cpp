/* Copyright Ciprian Ilies */

#include "gui_game_selector.hpp"

#include "../interface.hpp"

#include <iostream>

namespace gnomal
{

GUIGameSelector::GUIGameSelector(CEGUI::GUIContext &context, Interface &interface) : d_fileFilter(std::string(".")), context(context), interface(interface)
{
	frame = nullptr;
	root = nullptr;
	hidden = true;
	selection_result = "";
}

GUIGameSelector::~GUIGameSelector(void)
{
	if (!hidden) //Failsafe so that the data gets deleted if for some reason the user calls this instead of hide(). Warning: If the interface no longer exists or something like that, then the callback is bork and will result in stupidity when hide() calls it, so you STILL shouldn't call this directly. Safest bet is to use hide().
		hide();
}

bool GUIGameSelector::handleClick(const CEGUI::EventArgs &e)
{
	CEGUI::String buttonName = static_cast<const CEGUI::WindowEventArgs&>(e).window->getName();

	if (buttonName == "FolderList")
	{
		CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(context.getRootWindow()->getChild("FolderSelector/Frame/FolderList"));
		CEGUI::ListboxTextItem* item = static_cast<CEGUI::ListboxTextItem*>(list->getFirstSelectedItem());
		if (item == NULL)
		{
			return 0;
		}
		std::string text = item_list[item->getID()];
		selection_result = text;
		root->getChild("FolderSelector/Frame/Ok")->setEnabled(true); //Enable the okay button when something is selected.
	}
	if (buttonName == "Cancel")
	{
		selection_result = ""; //No dir selected.
		hide();
	}
	if (buttonName == "Ok")
	{
		hide();
		//TODO: In addition, have the interface add the selected folder as a new resource directory. Somehow. Let the callback handle it I guess. Which means modifying it to do so. Oh boy.
	}
	return false;
}

std::string GUIGameSelector::getResult()
{
	return selection_result;
}

void GUIGameSelector::wireEvents()
{
	root->getChild("FolderSelector/Frame/Ok")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIGameSelector::handleClick, this));
	root->getChild("FolderSelector/Frame/Cancel")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIGameSelector::handleClick, this));
	root->getChild("FolderSelector/Frame/FolderList")->subscribeEvent(CEGUI::Listbox::EventMouseClick, CEGUI::Event::Subscriber(&GUIGameSelector::handleClick, this));
}

void GUIGameSelector::show(CEGUI::Window *the_root, std::string directory)
{
	hidden = false;
	root = the_root;
	selection_result = "";
	frame = interface.interface->createVirtualWindowFromLayout(GUI_LAYOUT_FILE_SELECTOR);
	root->addChild(frame);
	wireEvents();
	root->getChild("FolderSelector/Frame/Ok")->setEnabled(false); //Disable the okay button when something isn't selected.
	updateGameList(directory);
}

void GUIGameSelector::hide()
{
	hidden = true;
	closeCallback(&interface, selection_result);
	if (frame)
	{
		frame->destroy();
	}
	frame = NULL;
	delete this; //Commit suicide.
}

void GUIGameSelector::validateGames(std::string directory)
{
	std::vector<std::string>::iterator iter;
	for (iter = item_list.begin(); iter != item_list.end(); ++iter)
	{
		std::string filename = directory;
		GEngine::mstring::addTailIfNone(filename, "/");
		filename += (*iter) + "/" + "lib" +  (*iter) + ".so";
		if (!GEngine::mfile::FileManager::fileExists(filename)) //Check to see if the module even has the module file.
		{
			std::cout << "[GUIGameSelector] Failed to validate \"" << filename << "\"\n";
			//Remove this item.
			item_list.erase(iter);
			iter--;
		}
		else
		{
			std::cout << "[GUIGameSelector] Validated \"" << filename << "\"\n";
		}
	}
}

void GUIGameSelector::updateGameList(std::string directory)
{
	//Clear previous listbox contents.
	CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(root->getChild("FolderSelector/Frame/FolderList"));
	list->resetList();

	item_list.clear();
	GEngine::mfile::FileManager::getFolders(directory, item_list);
	validateGames(directory); //Removes all folders that do not have a valid module.

	std::vector<std::string>::iterator iter;
	unsigned int n = 0;
	for (iter = item_list.begin(); iter != item_list.end(); ++iter)
	{
		CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem((*iter));
		item->setSelectionBrushImage("TaharezLook/GenericBrush"); //TODO: Double check name.
		item->setID(n);
		list->addItem(item);
		n++;
	}

	CEGUI::Editbox* box = static_cast<CEGUI::Editbox*>(context.getRootWindow()->getChild("FolderSelector/Frame/Address"));
	box->setText("Game Modules");
}

} //namespace gnomal
