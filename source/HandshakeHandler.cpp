#include "HandshakeHandler.h"

HandshakeHandler::HandshakeHandler()
{
	// Constructor
}

HandshakeHandler::~HandshakeHandler()
{
	// Destructor
}

// Trims whitespaces at front and end of string
std::string HandshakeHandler::trim(std::string str)
{
	char* whitespace = " \t\n\r";

	// Searches the string for the last character that does not match any of the characters specified in its arguments.
	std::string::size_type fpos = str.find_last_not_of(whitespace); 

	// Was fpos found?
	if (fpos != std::string::npos) {
		str.erase(fpos + 1); // Erase trailing whitespace
		// Searches the string for the first character that does not match any of the characters specified in its arguments.
		fpos = str.find_first_not_of(whitespace);
		// Was fpos found?
		if (fpos != std::string::npos) {
			str.erase(0, fpos); // Erase leading whitespace
		}
	}

	return str;
}

// Explodes a string into separate strings by a delimiter
std::vector<std::string> HandshakeHandler::explode(const std::string& str, char del)
{
	std::string next;
	std::vector<std::string> result;

	// Iterate through each character of the string
	for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
		// If we've hit the delimiting character
		if (*it == del) {
			// If we have some characters collected, then add to result vector
			if (!next.empty()) {
				result.push_back(next);
				next.clear();
			}
		} else {
			// Collect the next character into the sequence
			next += *it;
		}
	}

	if (!next.empty()) {
		result.push_back(next);
	}

	return result;
}