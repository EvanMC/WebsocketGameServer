#include "HandshakeHandler.h"
#include "util\SHA1.h"
#include "util\BASE64.h"
#include "Connection.h"
#include <iomanip>

HandshakeHandler::HandshakeHandler(std::string handshake) : h_handshake(handshake)
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
	char whitespace = ' ';

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
std::vector<std::string> HandshakeHandler::explode(const std::string &str, std::string delim)
{
	std::vector<std::string> explodeVector;
	int end = 0, start = 0, length = 0;

	// Find location of next delimiting string
	end = str.find(delim, start);

	// While delimiting string is still found
	while (end != std::string::npos) {
		length = end - start; // Get length between start and end search for delimiting string
		explodeVector.push_back(str.substr(start, length)); // Push back the string between start location and length

		start = end + delim.size(); // Update start location
		end = str.find(delim, start); // Search again
	}

	return explodeVector;
}

// Explode header values into a map container
std::map<std::string, std::string> HandshakeHandler::explode_http(const std::string &str)
{
	std::map<std::string, std::string> map;

	// Split string by newline ("\r\n")
	std::vector<std::string> explodedStr = explode(str, "\r\n");

	// Iterate through each line and obtain header values
	for (size_t i = 1; i < explodedStr.size(); ++i) {
		const std::string& value = explodedStr[i];
		// Host: server.example.com
		size_t pos = value.find(':');
		if (pos != std::string::npos) {
			map[value.substr(0 /* TODO */, pos)] = trim(value.substr(pos + 1 /* TODO */, value.find("\r\n")));
		}
	}

	return map;
}

void HandshakeHandler::parseHandshake()
{
	std::string hndshk = h_handshake;
	int size = hndshk.length(); // Get the length of the message
	int endPosition = hndshk.find("\r\n\r\n"); // Find the location of the ending

	// If message is empty, do not parse handshake
	if (hndshk.empty()) {
		return;
	}

	// If end not found, do not parse handshake
	if (endPosition == std::string::npos) {
		return;
	}

	hndshk.resize(endPosition); // Trim off bad ends

	std::string http = "HTTP/";
	if (hndshk.find("GET") != std::string::npos) {
		size_t httpPos = hndshk.find(http);
		if (httpPos != std::string::npos) {
			float version;

			// Make sure a float value is captured
			try {
				version = std::stof(hndshk.substr(httpPos + http.length(), hndshk.find("\r\n")));
			} catch (std::exception& e) {
				std::cout << e.what() << std::endl;
			}

			// If version is 1.1+
			if (version >= minimumHttp) {
				auto& themap = explode_http(hndshk);

				host = themap["Host"];
				upgrade = themap["Upgrade"];
				connection = themap["Connection"];
				origin = themap["Origin"];
				key = themap["Sec-WebSocket-Key"] + handshake_guid;
			} else {
				// Bad, ERROR
				return;
			}
		}
	}
}

std::string HandshakeHandler::answerHandshake()
{
	// Initialization of SHA1 disgestion
	char digest[20];

	std::string answer = "";
	answer += "HTTP/1.1 101 Switching Protocols\r\n";
	answer += "Upgrade: " + upgrade + "\r\n";
	answer += "Connection: " + connection + "\r\n";

	SHA1 sha;
	sha.Input((char*)key.c_str(), key.length()); // Hash string using SHA1
	sha.Result((unsigned*)digest); // Get the resulting hash

	// Network byte order requires to be in big-endian order
	for (int i = 0; i<20; i += 4) {
		unsigned char c;

		c = digest[i];
		digest[i] = digest[i + 3];
		digest[i + 3] = c;

		c = digest[i + 1];
		digest[i + 1] = digest[i + 2];
		digest[i + 2] = c;
	}
	// Encode digest with Base64
	encoded_key = base64_encode((const unsigned char *)digest, 20);

	// Answer must end with double new-line for the client to recognize end-of-transmission
	answer += "Sec-WebSocket-Accept: " + encoded_key + "\r\n\r\n";

	return answer;
}