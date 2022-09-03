#include "ExecutionManager.hpp"

enum e_channel {
	INVITE_ONLY,
	CHANNEL_FOUND,
	USER_IS_IN_CHAN,
	BAD_CHANNEL_NAME,
	CHANNEL_NOT_FOUND
};

typedef std::pair<Channel::iterator, Channel::iterator>	iterator_pair;

static int	find_channel(iterator_pair it_pair, std::string channel_name, Client *client)
{
	Channel *channel = it_pair.first->second;

	if (it_pair.first == it_pair.second) { // if channel not found
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

static void	create_new_channel(Channel::map &channel_book, Client *client, std::string channel_name)
{
	Channel	*new_channel = new Channel(channel_name);
	// add channel to book
	channel_book.insert(Channel::pair(channel_name, new_channel));
	client->join_channel(new_channel); // add channel to client's joined_channel and client to channel's members
	new_channel->set_operator(client);
}

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
		// to lower cases
		for (std::string::size_type j = 0; j < channels[i].length(); ++j)
			channels[i][j] = std::tolower(channels[i][j]);
		if (channels[i][0] == '#'){ // channel name starts with # (# alone is a valid name)
			std::string			channel_name = channels[i];
			Channel::iterator	chan_it = _channel_book.find(channel_name);

			switch (find_channel(iterator_pair(chan_it, _channel_book.end()), channel_name, client))
			{
			case BAD_CHANNEL_NAME:
				_send_rpl(client, ERR_BADCHANNAME(channel_name), 479);
				break;
			case CHANNEL_NOT_FOUND:
				create_new_channel(_channel_book, client, channel_name);
				_send_channel_update(channel_name, client, MSG_JOIN(channel_name, client->get_nickname()));				
				break;
			case USER_IS_IN_CHAN:
				// send ERR_USERONCHANNEL and continue //this err is not in rfc join section
				break;
			case INVITE_ONLY:
				break;
			case CHANNEL_FOUND:
				client->join_channel(chan_it->second); // add channel to client's joined_channel and client to channel's members
				_send_channel_update(channel_name, client, MSG_JOIN(channel_name, client->get_nickname()));
				break;
			}

		}
	}
	return SUCCESS;
}
