/* Copyright Ciprian Ilies */

#include <iostream>

#include "buttbot.hpp"

namespace ai
{

namespace buttbot
{

extern LanguageModule *m_language;

} //namespace buttbot.

} //namespace ai


/*void Buttbot::startup()
{
	//First open/create the database.
	db = new mdata::sqlite::Database();
	db->open("data/ai/buttbot/test.db");

	//Now create a table.
	std::string column_args =
		"Word		Text	NOT NULL,"
		"Definition	Text	NOT NULL"
		;
	db->createTable("dictionary", column_args);
}

void Buttbot::define(std::string word, std::string definition)
{
	if (!db)
	{
		std::cout << "[ai::Buttbot::define()] ERROR: No database.\n";
		return;
	}

	std::string value_format = "(Word, Definition)";

	std::string values = "VALUES(" + word + ",\"" + definition + "\");";


	db->insert("dictionary", value_format, values);
}*/
