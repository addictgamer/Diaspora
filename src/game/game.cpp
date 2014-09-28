/* Copyright Ciprian Ilies */

#include "../global_defines.hpp"

#include <iostream>
#include <sstream>

#if OS == OS_WINDOWS
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#include <GEngine/audio/audio.hpp>

#include "worldsim/worldsim.hpp"

#include "../ai/buttbot/buttbot.hpp"
//#include "../ai/ai.hpp"

#include "interface/interface.hpp"

#include "game.hpp"

GEngine::maudio::AudioManager audio; //The audio module.

using namespace GEngine;

namespace gnomal
{

#define PORT 9899

#define GAME_NAME "Diaspora"
#define GAME_VERSION "2"

#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600
#define FULLSCREEN false
#define WINDOWNAME "Diaspora v00000002" //TODO: Make this thing be created at runtime.

mgfx::d2d::D2D d2d; //The 2D interface thingy.

std::thread *t_console = nullptr; //The thread that will be handling console input.

std::vector<std::string> console_input; //Whatever the user types into the console will be stored here.

Gamestate gamestate = GAMESTATE_TITLE;

Game game;

void readConsole()
{
	//Just read in data from the console.
	while (!game.quit)
	{
		std::string temp_str = "";

		//All of this hard work is to work around cin being blocking.
		#if OS != OS_WINDOWS
			pollfd cinfd[1];
			cinfd[0].fd = fileno(stdin);
			cinfd[0].events = POLLIN;
		#else
			HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
		#endif


		#if OS != OS_WINDOWS
			if (poll(cinfd, 1, 1000))
		#else
			if (WaitForSingleObject(h, 0) == WAIT_OBJECT_0)
		#endif
			{
				getline(std::cin, temp_str);
			}

		if (temp_str != "")
		{
			std::cout << "[CONSOLE] Input Received: \"" << temp_str << "\"\n";
			console_input.push_back(temp_str); //Now store the temp string in the console input vector for further processing.
		}
	}
}

void processServerCommand(std::string command, std::vector<std::string> *args = nullptr)
{
	std::cout << "Processing command: \"" << command << "\"\n";

	if (command == "/quit")
	{
		std::cout << "\n***SHUTTING DOWN***\n";
		game.quit = true;
	}
	else if (command == "/define")
	{
		if (!args)
		{
			std::cout << "\n***ERROR: NO ARGUMENTS PASSED TO \"" << command << "\"\n";
		}
		else if (args->size() < 2)
		{
			std::cout << "\n***ERROR: NOT ENOUGH ARGUMENTS PASSED TO \"" << command << "\"\n";
		}
		else
		{
			/*
			 * Two arguments:
			 * * Word
			 * * Definition
			 */

			/*
			 * NOTE ABOUT ARGS:
			 * You must use (*args) to access the vector's elements. Eg:
			 std::string something = (*args)[0];
			 */

			std::string word = (*args)[0];
			std::cout << "Teaching buttbot word: \"" << word << "\".\n";
			args->erase(args->begin());
			std::string definition("");
			mstring::formStringFromVector(*args, definition, " ");

			std::cout << "Definition: \"" << definition << "\".\n";

			//TODO: Tell the AI.
		}
	}
	else if (command == "/addTailIfNone")
	{
		if (!args)
		{
			std::cout << "\n***ERROR: NO ARGUMENTS PASSED TO \"" << command << "\"\n";
		}
		else if (args->size() < 2)
		{
			std::cout << "\n***ERROR: NOT ENOUGH ARGUMENTS PASSED TO \"" << command << "\"\n";
		}
		else
		{
			/*
			 * Two arguments:
			 * * string
			 * * char to append
			 */

			if ((*args)[1].size() != 1)
			{
				std::cout << "\n***ERROR: SECOND ARGUMENT CAN ONLY BE A CHAR.***\n";
			}
			else
			{
				std::string result = (*args)[0];
				GEngine::mstring::addTailIfNone(result, (*args)[1]);
				std::cout << "Result: \"" << result << "\"\n\n";
			}
		}
	}
	else
	{
		std::cout << "\n***ERROR: UNRECOGNIZED COMMAND***\n";
	}
}

Game::Game()
{
	//gamestate = GAMESTATE_TITLE;
	server = nullptr;
	client = nullptr;

	t_network = nullptr;

	quit = false;

	world = nullptr;

	name = "";
	version = "";
}

Game::~Game()
{
	//gamestate = GAMESTATE_TITLE;
	if (server)
	{
		server->stop();
	}
	if (client)
	{
		client->stop();
	}
	if (t_network)
	{
		t_network->join();
		delete t_network;
	}
	if (server)
	{
		delete server;
		server = nullptr;
	}
	if (client)
	{
		delete client;
		client = nullptr;
	}
	if (world)
	{
		delete world;
		world = nullptr;
	}
}

void Game::update()
{
	if (server)
	{
		serverUpdate();
	}
	else if (client)
	{
		clientUpdate();
	}

	//---------------------------------------
	//--Draw everything that needs drawing.--
	//---------------------------------------

	interface.windowUpdate(); //Update all of the windows.

	interface.update(); //Update the interface.

	interface.drawLevelOne(); //Backgrounds and whatnot.

	//Now update the gameworld.
	if (gamestate == GAMESTATE_INGAME)
	{
		if (world)
		{
			//TODO: Render the world and let the user modify it.
			world->render(d2d, interface.interface->font);
		}
	}

	interface.drawLevelTwo(); //Unknown.

	interface.drawLevelThree(); //Draw interface (cegui).

	interface.windowDraw(); //Draw all of the windows.
}

void Game::startServer()
{
	std::cout << "Starting server.\n";
	server = new mnet::Server;
	mnet::IDENTIFICATION_MESSAGE = name;
	mnet::IDENTIFICATION_MESSAGE += ".v";
	mnet::IDENTIFICATION_MESSAGE += version;
	mnet::IDENTIFICATION_MESSAGE += "\n";
	//Start the server. With error checking.
	if (!server->start(PORT))
	{
		std::cerr << "Failed to start server.\n";
		throw; //TODO: Proper error handling.
	}
	t_network = new std::thread(&mnet::Server::update, server); //Start the server thread

	std::cout << "\n\n\n";

	//ai::Buttbot* new_ai;
	//new_ai = new ai::Buttbot();
	//game_ai.push_back(new_ai);

	//game_ai[0]->startup();
}

void Game::serverUpdate()
{
	std::cout << "Updating server.\n";
	server->updateClients(); //Update all the connected clients.

	while (console_input.size() != 0)
	{
		if (console_input[0][0] == '/') //Received a command?
		{
			//TODO: Grab args.
			std::vector<std::string> args;
			mstring::splitString(console_input[0], ' ', args); //TODO: Make it not split strings if an arg is enclosed in quotes.
			std::string command = args[0];
			args.erase(args.begin());
			processServerCommand(command, &args);
		}
		else
		{
			std::string data_str = console_input[0];
			server->sendMessageToAll(data_str); //Send the message to all clients.
		}
		console_input.erase(console_input.begin()); //Remove the data from the vector.
	}

	if (world && world->camera)
	{
		//Let's let the user move the camera around.
		if (d2d.window)
		{
			std::vector<GEngine::mui::unhandledEvent>::iterator iter = interface.interface->unhandled_events.begin();
			for (; iter != interface.interface->unhandled_events.end(); ++iter) //Loop through all the events.
			{
				sf::Event &event = (*iter).event;
				mgfx::Window &window = (*iter).window;
				switch (event.type)
				{
					case sf::Event::KeyPressed:
						switch (event.key.code)
						{
							case sf::Keyboard::Left:
								world->moveCamera(-1, 0, 0); //Move camera left.
								break;
							case sf::Keyboard::Right:
								world->moveCamera(+1, 0, 0); //Move camera right.
								break;
							case sf::Keyboard::Up:
								world->moveCamera(0, -1, 0); //Move camera Up.
								break;
							case sf::Keyboard::Down:
								world->moveCamera(0, +1, 0); //Move camera Down.
								break;
							case sf::Keyboard::Dash: //Minus key
								world->moveCamera(0, 0, -1); //Move camera Below.
								break;
							case sf::Keyboard::Equal: //Equals key
								world->moveCamera(0, 0, +1); //Move camera Above.
							default:
								break;
						}
						break;
					case sf::Event::MouseButtonPressed:
						if (event.mouseButton.button == sf::Mouse::Left) {
							//Do something? Used to click a space. But that's not currently implemented...
						}
						break;
					default:
						break;
				}
			}
		}
	}
}

bool Game::createWorld()
{
	std::cout << "Creating world.\n";
	world = new World;
	if (!world->genTestworld(d2d)) //Generate new world, with error checking.
	{
		std::cout << "Error: (Game::createWorld()) Failed to generate new world.\n";
		// Now 'reset' the world.
		delete world;
		world = nullptr;
		return false; //TODO: Proper error handling.
	}

	return true;
}

void Game::startClient()
{
	std::cout << "Starting client.\n";
	/*client = new mnet::Client(); //Initialize a new client.
	if (!client->newConnection(server_address, PORT)) //Connect to the server. //TODO: Try this without the "!". The server will crash. Odd, eh?
	{
		std::cerr << "Failed to start client.\n";
		throw; //TODO: Proper error handling.
	}
	t_network = new std::thread(&mnet::Client::update, client); //Start the client thread. */
}

void Game::clientUpdate()
{
	std::cout << "Updating client.";
	std::string data_received = client->getData(); //Get any data the client may have recieved.
	if (data_received != "")
	{
		std::cout << "[CLIENT] Received: " << data_received << "\n";
	}

	while (console_input.size() != 0)
	{
		std::string data_str = console_input[0];
		console_input.erase(console_input.begin()); //Remove the data from the vector.
		client->sendMessage(data_str); //Send the message to all clients.
	}

	if (!client->running()) //Check if the client is still running. It's not running if it lost connection to the server.
	{
		std::cout << "\n\nWARNING: LOST CONNECTION TO SERVER (client object is no longer running).\nAborting.\n\n\n";
		quit = true;
	}
}

} //namespace gnomal

using namespace gnomal;

int main(int argc, char* argv[])
{
	std::cout << GAME_NAME << " Version Number: " << GAME_VERSION << "\n"; //Output the version number to the console.

	mmisc::mrand::setup(); //Setup the random stuff generator module.

	if (!audio.initialize())
	{
		std::cout << "Error: Failed to initialize audio.\n";
		return false;
	}

	//TODO: Move music to the game module.
	GEngine::maudio::Sound title_music;
	title_music.load("music/Epic Steampunk Music - Steampunk Spies-3T-tSEwHw4k.mp3", true, true); //Loop and strean.
	audio.playMusic(title_music);

	//Setup the d2d, with error checking.
	if (!d2d.setup())
	{
		std::cout << "Error: Failed to set up d2d.\n";
		return false;
	}

	if (!interface.initialize(d2d, WINDOWWIDTH, WINDOWHEIGHT, FULLSCREEN, WINDOWNAME)) //Initialize the interface, with error checking.
	{
		std::cout << "Error: Failed to initialize the interface.\n";
		return false;
	}

	gamestate = GAMESTATE_TITLE;

	t_console = new std::thread(&readConsole); //Start reading the console.

	while (!game.quit) {
		game.update();
	}

	if (t_console)
	{
		t_console->join();
		delete t_console;
	}

	return 0; //Success.
}
