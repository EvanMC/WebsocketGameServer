// Handshake Handler
//
// The role for this class is to handle the handshake that it is sent
// from the client when the connection opens.  You can read more about 
// the server-side responsibilies of the handshake in the link below:
// https://tools.ietf.org/html/rfc6455#section-4.2.1

#ifndef HANDSHAKEHANDLER_H
#define HANDSHAKEHANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

class HandshakeHandler
{
	public:
	// Constructor/Destructor
	HandshakeHandler(std::string);
	~HandshakeHandler();

	void parseHandshake();
	std::string answerHandshake();

	private:
	// Utility functions
	std::string trim(std::string);
	std::vector<std::string> explode(const std::string&, std::string);
	std::map<std::string, std::string> explode_http(const std::string&);
	

	// Main handshake string
	std::string h_handshake;

	// Captured information
	std::string connection;
	std::string host;
	std::string origin;
	std::string upgrade;
	std::string key;
	std::string encoded_key;

	// DO NOT CHANGE - THIS IS A GLOBALLY UNIQUE IDENTIFIER THAT COMPLIES WITH RFC6455
	const std::string handshake_guid = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
	float minimumHttp = 1.1;
};

#endif