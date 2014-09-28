/* Copyright Ciprian Ilies */

#include "gui_file_selector.hpp"

#include "../interface.hpp"

#include <iostream>

namespace gnomal
{


//GUIFileSelector::GUIFileSelector(CEGUI::GUIContext &context, Interface &interface, void (*close_callback)()) : d_fileFilter(std::string(".")), context(context), interface(interface)
//GUIFileSelector::GUIFileSelector(CEGUI::GUIContext &context, Interface &interface, std::function<void()> the_close_callback) : d_fileFilter(std::string(".")), context(context), interface(interface)
GUIFileSelector::GUIFileSelector(CEGUI::GUIContext &context, Interface &interface) : d_fileFilter(std::string(".")), context(context), interface(interface)
{
	//int(*compar)(const void *, const void *)
	frame = nullptr;
	root = nullptr;
	hidden = true;
	//disk = new DiskObject();
	selection_result = "";

	//close_callback = the_close_callback;
}

GUIFileSelector::~GUIFileSelector(void)
{
	//The hide() function handles it all.
	//delete disk;
	//disk = NULL;
	if (!hidden) //Failsafe so that the data gets deleted if for some reason the user calls this instead of hide(). Warning: If the interface no longer exists or something like that, then the callback is bork and will result in stupidity when hide() calls it, so you STILL shouldn't call this directly. Safest bet is to use hide().
		hide();
}

bool GUIFileSelector::handleClick(const CEGUI::EventArgs &e)
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
		//std::cout << "Text = \"" << text << "\"\n";
		if (text == "..")
		{
			current_directory = GEngine::mfile::FileManager::getParentDirectory(current_directory);
		}
		else
		{
			GEngine::mstring::addTailIfNone(current_directory, "/"); //do this.
			current_directory.append(text);
		}
		updateFolderList();
		selection_result = current_directory;
	}
	if (buttonName == "Cancel")
	{
		selection_result = ""; //No dir selected.
		hide();
	}
	if (buttonName == "Ok")
	{
		selection_result = current_directory;
		hide();
		//TODO: In addition, have the interface add the selected folder as a new resource directory. Somehow. Let the callback handle it I guess. Which means modifying it to do so. Oh boy.
	}
	return false;
}

void GUIFileSelector::setFolder(std::string path)
{
	//TODO: Turn it into absolute path.
	current_directory = GEngine::mfile::FileManager::getAbsolutePath(path);
	//current_directory = path;
	updateFolderList();
}

std::string GUIFileSelector::getResult()
{
	return selection_result;
}

void GUIFileSelector::wireEvents()
{
	root->getChild("FolderSelector/Frame/Ok")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIFileSelector::handleClick, this));
	root->getChild("FolderSelector/Frame/Cancel")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIFileSelector::handleClick, this));
	root->getChild("FolderSelector/Frame/FolderList")->subscribeEvent(CEGUI::Listbox::EventMouseDoubleClick, CEGUI::Event::Subscriber(&GUIFileSelector::handleClick, this));
}

void GUIFileSelector::show(CEGUI::Window *the_root)
{
	hidden = false;
	root = the_root;
	selection_result = "";
	frame = interface.interface->createVirtualWindowFromLayout(GUI_LAYOUT_FILE_SELECTOR);
	root->addChild(frame);
	wireEvents();
	updateFolderList();
}

void GUIFileSelector::hide()
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

void GUIFileSelector::updateFolderList()
{
	//Clear previous listbox contents.
	CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(root->getChild("FolderSelector/Frame/FolderList"));
	list->resetList();

	item_list.clear();
	if (current_directory != "/") //TODO: Make cross platform.
	{
		//Only add this if it's not in the root directory.
		item_list.push_back(".."); //TODO: Move into gengine.
	}
	GEngine::mfile::FileManager::getFolders(current_directory, item_list);

	std::vector<std::string>::iterator iter;
	unsigned int n = 0;
	for (iter = item_list.begin(); iter != item_list.end(); ++iter)
	{
		CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem((*iter));
		//item->setSelectionBrushImage("TaharezLook-Images/GenericBrush"); //TODO: Double check name.
		item->setSelectionBrushImage("TaharezLook/GenericBrush"); //TODO: Double check name.
		item->setID(n);
		list->addItem(item);
		n++;
	}

	CEGUI::Editbox* box = static_cast<CEGUI::Editbox*>(context.getRootWindow()->getChild("FolderSelector/Frame/Address"));
	box->setText(current_directory);

	//Valid folder? Enable/Disable OK //TODO: Make this customizable.
	/*std::vector<std::string> files;
	GEngine::mfile::FileManager::getFiles(current_directory, files, d_fileFilter);
	if (files.size() > 0) //TODO: Get files.
	{
		context.getRootWindow()->getChild("FolderSelector/Frame/Ok")->enable();
	}
	else
	{
		context.getRootWindow()->getChild("FolderSelector/Frame/Ok")->disable();
	}*/
	context.getRootWindow()->getChild("FolderSelector/Frame/Ok")->enable();
}

} //namespace gnomal
