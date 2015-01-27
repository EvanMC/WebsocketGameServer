#include "Connection.h"

Connection::Connection(tcp::socket socket) : w_socket(std::move(socket))
{
	// Constructor
}

void Connection::readMessage()
{
	auto self(shared_from_this());
	boost::asio::async_read_until(w_socket, streambuffer, "\r\n\r\n",
		[this, self](boost::system::error_code ec, std::size_t length)  // Lambda function
		{
			if (!ec)
			{
				std::istream is(&streambuffer);
				std::getline(is, w_data_s);

				std::cout << w_data_s << std::endl;
				sendMessage(length);
			}
		});
}

void Connection::sendMessage(std::size_t length)
{
	auto self(shared_from_this());
	boost::asio::async_write(w_socket, boost::asio::buffer(w_data_s, length),
		[this, self](boost::system::error_code ec, std::size_t /*length*/)  // Lambda function
		{
			if (!ec)
			{
				readMessage();
			}
		});
}