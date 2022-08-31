#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "commons.hpp"

class Client;

class Channel {

	public :
		Channel();
		//canonical form
		~Channel();
		// send_priv_msg(); //??
		void broadcast();

	private :
		std::string _name;
		std::string _topic;
		Client *_operator_client; //or operator_fd?? or username??
 
		std::map<std::string, Client*> _members; //client_name or fd or username // std::string client_name, Client* client

};

#include "Client.hpp"

#endif