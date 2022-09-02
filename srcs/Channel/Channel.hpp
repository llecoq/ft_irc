#ifndef CHANNEL_HPP
# define CHANNEL_HPP

// # include "Client.hpp"

# include <iostream>
# include <string>
# include <vector>
# include <map>

class Client;

enum e_mode
{
	INVITE_ONLY
};

class Channel
{

	public:

		typedef std::pair<std::string, Channel*>		pair;
		typedef std::map<std::string, Channel*>			map;
		typedef map::iterator							iterator;

		Channel(std::string name);
		Channel( Channel const & src );
		~Channel();

		Channel &		operator=( Channel const & rhs );

		// accessors
		std::string	get_name() const;
		int			get_mode() const;
		void		set_operator(Client *client);
		
		// methods
		void		add_member(Client *client);
		bool		user_is_in_channel(Client *client);
		// void	broadcast(int client_fd, std::string msg);

	private:
		
		Channel();
		
		std::string				_name;
		std::string				_topic;
		int						_mode;
		Client					*_operator;
		std::vector<Client *>	_members;

// 		std::map<std::string, Client*> _members; //client_name or fd or username // std::string client_name, Client* client

};

std::ostream &			operator<<( std::ostream & o, Channel const & i );

#endif /* ********************************************************* CHANNEL_H */