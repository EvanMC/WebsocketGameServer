#include "Connection.h"
#include "HandshakeHandler.h"

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
				// Initialize HandshakeHandler with incoming handshake message
				HandshakeHandler newHandshake(w_data);
				// Parse the incoming handshake message
				newHandshake.parseHandshake(); 
				// Store constructed answer into w_data_s
				w_handshake_answer = newHandshake.answerHandshake(); 

				std::cout << "Connection established!" << std::endl;

				// Send the answer back to the client
				sendMessage(w_handshake_answer.length());
			}
		});
}

void Connection::sendMessage(std::size_t length)
{
	auto self(shared_from_this());
	boost::asio::async_write(w_socket, boost::asio::buffer(w_handshake_answer, length),
		[this, self](boost::system::error_code ec, std::size_t /*length*/)  // Lambda function
		{
			if (!ec)
			{
				// Listen for more messages
				readMessage();
			}
		});
}