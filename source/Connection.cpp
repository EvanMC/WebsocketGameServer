#include "Connection.h"

Connection::Connection(tcp::socket socket) : w_socket(std::move(socket))
{
	// Constructor
}

void Connection::readMessage()
{
	auto self(shared_from_this());
	w_socket.async_read_some(boost::asio::buffer(w_data, max_length),
		[this, self](boost::system::error_code ec, std::size_t length)  // Lambda function
		{
			if (!ec)
			{
				std::cout << w_data << std::endl;
				sendMessage(length);
			}
		});
}

void Connection::sendMessage(std::size_t length)
{
	auto self(shared_from_this());
	boost::asio::async_write(w_socket, boost::asio::buffer(w_data, length),
		[this, self](boost::system::error_code ec, std::size_t /*length*/)  // Lambda function
		{
			if (!ec)
			{
				readMessage();
			}
		});
}