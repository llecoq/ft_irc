#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "commons.hpp"
#include "numeric_replies.hpp"

class Client;

class Channel
{

	public:
		typedef std::pair<std::string, Channel*>		pair;
		typedef std::map<std::string, Channel*>			map;
		typedef map::iterator							iterator;

		Channel(std::string name);
		Channel( Channel const & src );
		~Channel();

		Channel &			operator=( Channel const & rhs );

		// accessors
		std::string	get_name() const;
		std::string	get_topic() const;
		std::string	get_modes() const;
		Client*		get_operator() const;
		void		set_operator(Client *client);
		void		set_modes(char c, size_t pos, char add_rmv);
		
		// methods
		void		broadcast(Client *client, std::string msg);
		void		add_member(Client *client);
		bool		user_is_in_channel(Client *client);
		std::string	list_members();

	private:
		
		Channel();
		
		std::string				_name;
		std::string				_topic;
		std::string				_modes;
		Client					*_operator;
		std::vector<Client *>	_members;

};

std::ostream &				operator<<( std::ostream & o, Channel const & i );

#include "Client.hpp"

#endif /* ********************************************************* CHANNEL_H */