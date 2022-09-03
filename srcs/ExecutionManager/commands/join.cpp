#include "ExecutionManager.hpp"

enum e_channel {
	IGNORE,
	INVITE_ONLY,
	CHANNEL_FOUND,
	USER_IS_IN_CHAN,
	BAD_CHANNEL_NAME,
	CHANNEL_NOT_FOUND
};

static int	find_channel(Channel::map &channel_book, std::string &channel_name, Client *client);
static void	create_new_channel(Channel::map &channel_book, Client *client, std::string channel_name);

int ExecutionManager::join(Client *client, token_vector tokens) {
	std::string	cmd("JOIN");

	if (client->get_authentication() == false) {
		return _send_rpl(client, ERR_NOTREGISTERED, 451);
	}
	if (tokens.size() < 2){
		return _send_rpl(client, ERR_NEEDMOREPARAMS(cmd), 461);
	}
	// too many params does not exists because server just create chan with first param (tested on freenode)
	token_vector			channels = _split(tokens[1], ",");

	for (size_t  i = 0; i < channels.size(); i++) {
		switch (find_channel(_channel_book, channels[i], client))
		{
		case BAD_CHANNEL_NAME:
			_send_rpl(client, ERR_BADCHANNAME(channels[i]), 479);
			break;
		case CHANNEL_NOT_FOUND:
			create_new_channel(_channel_book, client, channels[i]);
			_send_channel_update(channels[i], client, MSG_JOIN(channels[i], client->get_nickname()));				
			break;
		case USER_IS_IN_CHAN:
			// send ERR_USERONCHANNEL and continue //this err is not in rfc join section
			break;
		case INVITE_ONLY:
			break;
		case CHANNEL_FOUND:
			client->join_channel(_channel_book.find(channels[i])->second); // add channel to client's joined_channel and client to channel's members
			_send_channel_update(channels[i], client, MSG_JOIN(channels[i], client->get_nickname()));
			break;
		}
	}
	return SUCCESS;
}

static int	find_channel(Channel::map &channel_book, std::string &channel_name, Client *client)
{
	for (std::string::size_type i = 0; i < channel_name.length(); ++i)
		channel_name[i] = std::tolower(channel_name[i]);
	
	if (channel_name[0] == '#') { // channel name starts with # (# alone is a valid name)
		Channel::iterator	chan_it = channel_book.find(channel_name);
		Channel	*channel = chan_it->second;

		if (chan_it == channel_book.end()) { // if channel not found
			if (channel_name.size() > 50)
				return BAD_CHANNEL_NAME;
			return CHANNEL_NOT_FOUND;
		}
		else {
			if (channel->user_is_in_channel(client) == true)
				return USER_IS_IN_CHAN;
			if (channel->get_mode() == INVITE_ONLY)
				return INVITE_ONLY;
			return CHANNEL_FOUND;
		}
	}
	return IGNORE;
}

static void	create_new_channel(Channel::map &channel_book, Client *client, std::string channel_name)
{
	Channel	*new_channel = new Channel(channel_name);
	channel_book.insert(Channel::pair(channel_name, new_channel)); // add channel to _channel_book
	client->join_channel(new_channel); // add channel to client's joined_channel and client to channel's members
	new_channel->set_operator(client);
}
