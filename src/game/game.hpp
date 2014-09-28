/* Copyright Ciprian Ilies */

#pragma once

#include <thread>
#include <GEngine/GEngine.hpp>

namespace GEngine
{

namespace maudio
{

class AudioManager;

} //namespace maudio

} //namespace GEngine

extern GEngine::maudio::AudioManager audio; //The audio module.

namespace ws
{

class World;

} //namespace ws

namespace gnomal
{

enum Gamestate
{
	GAMESTATE_TITLE,
	GAMESTATE_INGAME
} extern gamestate;

class World;


/*
 * TODO:
 * Make this a base game class and then make the loader take a module, execute its createGame() function, and then execute all of its code, which can draw into this project's code as a base for that.
 */
class Game
{
protected:
	GEngine::mnet::Server *server; //This is the server (for networking).
	GEngine::mnet::Client *client; //This is the client (for networking).

	std::thread *t_network; //The thread running the server (or client).

	std::string name; //The game's name.
	std::string version; //The game's version.	
public:
	//Gamestate gamestate; //The game's gamestate.

	bool quit; //Quit the game?

	World *world;
	explicit Game();
	virtual ~Game();

	virtual void update();

	//------Server Functions------
	virtual void startServer();
	virtual void serverUpdate();
	virtual bool createWorld();

	//------Client Functions------
	virtual void startClient();
	virtual void clientUpdate();
} extern game;

} //namespace gnomal
