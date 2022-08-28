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
{
	std::cout << "server destructor" << std::endl;
	client_iterator	it;

	_close_all_fds();
	for (it = _client_book.begin(); it != _client_book.end(); it++)
		delete it->second;	
	// _delete_clients_from_book(); // FREE ALL CLIENTS
}

/*
** ---------------------------------- MEMBERS ---------------------------------
*/

void	Server::init()
{
	_get_address_info();
	_get_listening_socket();
	_listen_for_incoming_connections();		
}

void	Server::_signal_handler(int signum)
{
	(void)signum;
	throw serverExceptions("Server: ", "shutting down...");
}

void	Server::run()
{
	while (1) 					// main loop
	{
		signal(SIGINT, _signal_handler);
		_poll_events(); 		// wait for events
		for (pollfd_iterator it = _pollfd.begin(); it < _pollfd.end(); it++)
		{
			switch (_find_event(*it))
			{
			case PENDING_CONNECTION:
				_log("PENDING CONNECTION");
				_accept_pending_connection();
				break;
			case CONNECTION_LOST:
				std::cout << "CONNECTION LOST: socket " << it->fd << std::endl;
				// print client ?
				_close_connection(it);
				break;
			case DATA_RECEIVED:
				std::cout << "DATA RECEIVED: socket " << it->fd << std::endl;
				_process_data(it);
				break;
			case NO_EVENT:
				// std::cout << "no event : socket " << (*it).fd << std::endl;
				break;
			case ERR_RECV:
				_log("err recv");
				break;
			}
		}	
	}
}