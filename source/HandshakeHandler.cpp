#include <iostream>
#include <string>
#include "HandshakeHandler.h"

HandshakeHandler::HandshakeHandler()
{
	// Constructor
}

HandshakeHandler::~HandshakeHandler()
{
	// Destructor
}

//
std::string HandshakeHandler::trim(std::string str)
{
	char* whitespace = " \t\n\r";

	// Searches the string for the last character that does not match any of the characters specified in its arguments.
	std::string::size_type fpos = str.find_last_not_of(whitespace); 

	// Was fpos found?
	if (fpos != std::string::npos)
	{
		str.erase(fpos + 1); // Erase trailing whitespace

		// Searches the string for the first character that does not match any of the characters specified in its arguments.
		fpos = str.find_first_not_of(whitespace);
		
		// Was fpos found?
		if (fpos != std::string::npos)
		{
			str.erase(0, fpos); // Erase leading whitespace
		}
	}

	return str;
}