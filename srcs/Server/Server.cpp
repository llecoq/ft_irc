#include "Server.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server(const char* port, const char* password)
:
	_server_info(port, password)
{
	// if (port > 1024)
		// exit zobi ?
	// if password ... exit ?
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

void	Server::run()
{
	while (1) 					// main loop
	{
		_poll_events(); 		// wait for events
		for (pollfd_iterator it = _pollfd.begin(); it < _pollfd.end(); it++)
		{
			switch (_find_event(*it))
			{
			case PENDING_CONNECTION:
				_accept_pending_connection();
				break;
			case CONNECTION_LOST:
				std::cout << "connection lost : socket " << (*it).fd << std::endl;
				// print client ?
				_close_connection(it);
				break;
			case DATA_RECEIVED:
				std::cout << "data received : socket " << (*it).fd << std::endl;
				_process_data(it);
				break;
			case NO_EVENT:
				// std::cout << "no event : socket " << (*it).fd << std::endl;
				break;
			}
		}	
	}
}