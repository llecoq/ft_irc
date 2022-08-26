#include "Server.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server(const char* port, const char* password)
:
	_server_info(port, password)
{
	(void)_server_info.password;
	_pollfd.reserve(10);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Server::~Server()
{}

/*
** ---------------------------------- MEMBERS ---------------------------------
*/

void	Server::init()
{
	try
	{
		_get_address_info();
		_get_listening_socket();
		_listen_for_incoming_connections();		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	    exit(EXIT_FAILURE);
	}
}