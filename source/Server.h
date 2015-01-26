#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Server
{
	public:
	Server(boost::asio::io_service& w_io_service, short w_port);
	~Server();

	private:
	void accept();

	tcp::acceptor w_acceptor;
	tcp::socket w_socket;
};

#endif