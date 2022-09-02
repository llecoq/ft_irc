#ifndef CHANNEL_HPP
# define CHANNEL_HPP

// # include "Client.hpp"

# include <iostream>
# include <string>

class Channel
{

	public:

		Channel();
		Channel( Channel const & src );
		~Channel();

		Channel &		operator=( Channel const & rhs );

		// void	broadcast(int client_fd, std::string msg);

	private:
		
		std::string		_name;
		std::string		_topic;
		// Client			*_operator;
		// 		std::string _name;
// 		std::string _topic;
// 		Client *_operator_client; //or operator_fd?? or username??
 
// 		std::map<std::string, Client*> _members; //client_name or fd or username // std::string client_name, Client* client

};

std::ostream &			operator<<( std::ostream & o, Channel const & i );

#endif /* ********************************************************* CHANNEL_H */