#include "Channel.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel() {}

Channel::Channel(std::string name) : _name(name){(void)_name;}

Channel::Channel( const Channel & src )
{
	(void)src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Channel::~Channel()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Channel &				Channel::operator=( Channel const & rhs )
{
	(void)rhs;
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Channel const & i )
{
	(void)i;
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void	Channel::broadcast(Client *client, std::string msg)
{
	for (size_t i = 0; i < _members.size(); i++)
		if (_members[i] != client)
			send(_members[i]->get_fd(), msg.c_str(), msg.size(), 0);
}

void	Channel::add_member(Client *client)
{
	_members.push_back(client);
}

void	Channel::erase_member(Client *client, std::string message)
{
	std::vector<Client *>::iterator	it;

	for (it = _members.begin(); it < _members.end(); it++)
	{
		if (*it == client)
		{
			_members.erase(it);
			broadcast(NULL, MSG_PART(_name, client->get_nickname(), message));
			return ;
		}
	}
}

bool	Channel::user_is_in_channel(Client *client)
{
	for (size_t i = 0; i < _members.size(); i++)
		if (_members[i] == client)
			return true;
	return false;	
}

std::string	Channel::list_members()
{
	std::string	members;

	for (size_t i = 0; i < _members.size(); i++)
		members.append(_members[i]->get_nickname() + " ");
	return members;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string	Channel::get_name() const
{
	return _name;
}

std::string	Channel::get_topic() const
{
	return _topic;
}

std::string	Channel::get_mode() const
{
	return _mode;
}

void	Channel::set_operator(Client *client)
{
	_operator = client;
}

/* ************************************************************************** */