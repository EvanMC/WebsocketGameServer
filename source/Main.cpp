#include "Server.h"
#include "util/SHA1.h"
#include "util/BASE64.h"

const std::string version_number = "0.0.3";

int main()
{
	std::cout << "Initial Game Server [version: " << version_number << "]" << std::endl << std::endl;

	boost::asio::io_service io_service;
	Server serv(io_service, 9554);

	io_service.run();

	system("PAUSE");
	return 0;
}