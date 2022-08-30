#ifndef SERVER_HPP
#define SERVER_HPP

#include "Commons.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Execution.hpp"

class Server {

	public :
		Server();
		//canonical form
		~Server();

		void run();
		void function_that_adds_client();

		Client &function_that_does_receive();//Get msg in client buf
	
		Execution exec;

		// std::string parse(Client &client);//does the parsing
			//search_for_backslash_n(); //;
		// void execution(Client &client);

		// receiving_client = function_that_does_receive();//Get msg in client buf
		// while ((command = parsing(receiving_client)).empty() == 0) //as long as parsing returns commands, then execute them
			// execution(receiving_client, command);


	private :
		std::vector<struct pollfd>	_pollfd;
		std::map<std::string, Client *> _client_book; // std::string client_name, Client *client
		std::map<std::string, Channel *> _channel_book; // std::string client_name, Channel *channel
		// std::map<std::string, intptr*fun()> _cmd_book; //LOOK UP FUNCTION PTR // std::string command_name, ptr*fun()
		// Parser _parser; //ptr ?

};

#endif