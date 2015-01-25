// Handshake Handler
//
// The role for this class is to handle the handshake when it is sent
// by the client when the connection opens.  You can read more about 
// the server-side responsibilies of the handshake in the link below:
// https ://tools.ietf.org/html/rfc6455#section-4.2.1

#ifndef HANDSHAKEHANDLER_H
#define HANDSHAKEHANDLER_H

#include <iostream>
#include <string>

class HandshakeHandler
{
	public:
	HandshakeHandler();
	~HandshakeHandler();

	std::string trim(std::string);

	private:
	std::string resource;
	std::string host;
	std::string origin;
	std::string protocol;
	std::string key;

	// DO NOT CHANGE - THIS IS A GLOBALLY UNIQUE IDENTIFIER THAT COMPLIES WITH RFC6455
	const std::string handshake_guid = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
};

#endif