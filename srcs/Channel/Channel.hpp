#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "commons.hpp"
#include "numeric_replies.hpp"

class Client;

class Channel
{

	public:
		typedef std::map<std::string, Client*>			members_map;
		typedef members_map::iterator					members_iterator;

		Channel();
		Channel( Channel const & src );
		~Channel();

		Channel &			operator=( Channel const & rhs );

		members_map			members; //client_name or fd or username
		// void	broadcast(int client_fd, std::string msg);

	private:
		
		std::string			_name;
		std::string			_topic;
		// Client			*_operator;
		// 		std::string _name;
// 		std::string _topic;
// 		Client *_operator_client; //or operator_fd?? or username??
 

};

std::ostream &				operator<<( std::ostream & o, Channel const & i );

#include "Client.hpp"
#endif /* ********************************************************* CHANNEL_H */