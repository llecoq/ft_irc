//ifndef

#include "Commons.hpp"

class Server {

		Server();
		//canonical form
		~Server();

		void parse(Client &client);//does the parsing
			//search_for_backslash_n(); //; 


	private :
		std::vector<struct pollfd>	_pollfd;
		std::map<std::string client_name, Client *> _client_book;
		std::map<std::string channel_name, Channel *> _channel_book;
		std::map<std::string command_name, ptr*fun()> _cmd_book; //LOOK UP FUNCTION PTR
		Parser _parser; //ptr ?

};

int main()
{
	Server;

	server->parser(client);//should be caopabke of adding a channel


}