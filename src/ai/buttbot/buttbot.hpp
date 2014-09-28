/* Copyright Ciprian Ilies */

/*
 * AI something or other.
 */

/* 
 * How about I try a...component-based artificial intelligence, where all the components/modules communicate with eachother to achieve the illusion of intelligence -- Distributed Artifical Intelligence.
 * So, there can be a language module,
 */

#pragma once

#include <sqlite3.h>

#include <GEngine/data/sqlite.hpp>

// Commented out because it doesn't exist
//#include "../ai.hpp"

namespace ai
{

namespace buttbot
{

/*
 * Handles all language related stuff. Stores definitions of words, contains grammar rules, etc.
 */
class LanguageModule
{
public:
	LanguageModule();
	~LanguageModule();
} extern *m_language;

//TODO: Insert classes here that...make the AI work.

/*
So, what other classes would be needed?
*/

} //namespace buttbot

} // namespace ai








/* *** Old AI Code */
/*namespace ai
{

class AI
{
public:
	//TODO: Some words database.

	AI() {}
	~AI() {}

	// * Starts up the AI (such as creating/opening the database, etc).
	// * Throws an exception on failure. TODO: Document exception type and whatnot.
	virtual void startup() {};

	// * Tells the AI something.
	virtual void say(std::string message) {};

	// * Defines a word and adds it to the database.
	virtual void define(std::string word, std::string definition) {};
};

class Buttbot : public AI
{
private:
	mdata::sqlite::Database *db;
public:
	Buttbot()
	{
		db = nullptr;
	}
	~Buttbot()
	{
		if (db)
		{
			delete db;
			db = nullptr;
		}
	}

	// * Startup buttbot.
	// * Opens the database and stuff.
	// * Inherited from AI: virtual void startup() {};
	void startup();

	// * Defines a word and adds it to the database.
	void define(std::string word, std::string definition);
};


} //namespace ai*/
