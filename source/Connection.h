#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>
#include <string>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Connection : public std::enable_shared_from_this<Connection>
{
	public:
	Connection(tcp::socket socket);

	void startConnection() { readMessage(); };

	private:
	void readMessage();
	void sendMessage(std::size_t);

	boost::asio::streambuf streambuffer;
	tcp::socket w_socket;

	// Using string type for now
	std::string w_handshake_answer;

	// Temporarily left out
	enum { max_length = 1024 };
	char w_data[max_length];
};

#endif