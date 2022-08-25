//ifndef

#include "Commons.hpp"

class Server {

		Server();
		//canonical form
		~Server();

		run();
		function_that_adds_client();

		Client &function_that_does_receive();//Get msg in client buf

		std::string parse(Client &client);//does the parsing
			//search_for_backslash_n(); //; 
		void execution(Client &client, std::string);

		// receiving_client = function_that_does_receive();//Get msg in client buf
		// while ((command = parsing(receiving_client)).empty() == 0) //as long as parsing returns commands, then execute them
			// execution(receiving_client, command);

	private :
		std::vector<struct pollfd>	_pollfd;
		std::map<std::string client_name, Client *> _client_book;
		std::map<std::string channel_name, Channel *> _channel_book;
		std::map<std::string command_name, ptr*fun()> _cmd_book; //LOOK UP FUNCTION PTR
		Parser _parser; //ptr ?

};
