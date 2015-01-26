#include "Server.h"
#include "Connection.h"

Server::Server(boost::asio::io_service& io_service, short w_port)
	: w_acceptor(io_service, tcp::endpoint(tcp::v4(), w_port)), w_socket(io_service)
{
	accept();
}

Server::~Server()
{
	// Destructor
}

void Server::accept()
{
	w_acceptor.async_accept(w_socket, 
		[this](boost::system::error_code ec) // Lambda function
		{
			if (!ec)
			{
				std::make_shared<Connection>(std::move(w_socket))->startConnection();
			}
			accept();
		});
}