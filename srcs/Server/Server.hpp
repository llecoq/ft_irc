#ifndef SERVER_HPP
# define SERVER_HPP

#include "Commons.hpp"
// #include "Client.hpp"
#include "Exceptions.hpp"

// à mettre dans common ?
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <stdlib.h>
# include <poll.h>
# include <stdio.h>
# include <unistd.h>

enum	e_event
{
	PENDING_CONNECTION,
	CONNECTION_LOST,
	DATA_RECEIVED,
	NO_EVENT
};

struct	t_server_info
{
	t_server_info(const char* prt, const char* pass) : port(prt), password(pass) {}

	const char*			port;
	const char*			password;
	struct addrinfo*	servinfo;
	int					listening_socket;
};

class Server
{

	public :

		// member types
		typedef std::vector<struct pollfd>		pollfd_vector;
		typedef pollfd_vector::iterator			pollfd_iterator;
		// typedef std::map<>

		// constructors & destructor
		Server(const char* port, const char* password);
		~Server();

		// member functions
		void	init();
		void	run();
		// function_that_adds_client();

		// Client &function_that_does_receive();//Get msg in client buf

		// std::string parse(Client &client);//does the parsing
			//search_for_backslash_n(); //; 
		// void execution(Client &client, std::string);

		// receiving_client = function_that_does_receive();//Get msg in client buf
		// while ((command = parsing(receiving_client)).empty() == 0) //as long as parsing returns commands, then execute them
			// execution(receiving_client, command);

	private :
		
		pollfd_vector		_pollfd;
		t_server_info		_server_info;					

		// std::map<std::string client_name, Client *> _client_book;
		// std::map<std::string channel_name, Channel *> _channel_book;
		// std::map<std::string command_name, ptr*fun()> _cmd_book; //LOOK UP FUNCTION PTR

		// UTILS FUNCTIONS
		// init()
		void				_get_address_info();
		void				_get_listening_socket();
		int					_create_and_bind_socket(addrinfo* ptr);
		void				_bind_socket();
		void				_listen_for_incoming_connections();
		// run()
		void				_poll_events();
		int					_find_event(pollfd current_pollfd);
		void				_accept_pending_connection();
		// void				_add_client_to_book();
		void				_process_data(pollfd_iterator it);
		void				_close_connection(pollfd_iterator it);
		// error and log management
		void				_error_exit(int error, std::string error_msg);
		void				_log(std::string log_msg);
		void				_err_log(std::string err_msg);
		void				_close_all_fds();

};

#endif /* ********************************************************** SERVER_HPP */