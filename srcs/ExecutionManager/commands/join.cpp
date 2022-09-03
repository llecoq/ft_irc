#include "ExecutionManager.hpp"

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

			if (chan_it == _channel_book.end()){ // channel does not exists
				if (channel_name.size() > 50){
					_send_rpl(client, ERR_BADCHANNAME(channel_name), 479);
					continue;
				}
				Channel	*new_channel = new Channel(channel_name);
				// add channel to book
				_channel_book.insert(Channel::pair(channel_name, new_channel));
				client->join_channel(new_channel); // add channel to client's joined_channel and client to channel's members
				new_channel->set_operator(client);
				_send_channel_update(new_channel, client, MSG_JOIN(channel_name, client->get_nickname()));				
				continue;
			}
			else { // channel exists
				Channel	*channel = chan_it->second;

				// A TESTER
				if (channel->user_is_in_channel(client) == true) {
					// send ERR_USERONCHANNEL and continue //this err is not in rfc join section
					return 443;
				}
				if (channel->get_mode() == INVITE_ONLY) {
					// still have to handle modes in Channel
		 			//send ERR_INVITEONLYCHAN
					return 473;
				}
				client->join_channel(channel); // add channel to client's joined_channel and client to channel's members
				_send_channel_update(channel, client, MSG_JOIN(channel_name, client->get_nickname()));
				continue;
			}
		}
	}
	return SUCCESS;
}