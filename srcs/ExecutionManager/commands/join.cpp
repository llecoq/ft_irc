#include "ExecutionManager.hpp"

unsigned int ExecutionManager::join(Client *client, token_vector tokens) {
	std::string	cmd("JOIN");
	std::string	msg;

	if (client->get_authentication() == false)
		return 0; // or msg ? ERR_NOTREGISTERED
	if (tokens.size() < 2){
		msg = ERR_NEEDMOREPARAMS(cmd);
		send(client->get_fd(), msg.c_str(), msg.size(), 0);
		return 461;
	}
	// too many params does not exists because server just create chan with first param (tested on freenode)
	token_vector			channels = _split(tokens[1], ",");

	for (size_t  i = 0; i < channels.size(); i++) {
		// to lower cases
		for (std::string::size_type j = 0; j < channels[i].length(); ++j)
			channels[i][j] = std::tolower(channels[i][j]);
		if (channels[i][0] == '#'){ // channel name starts with #
			std::string			channel_name = channels[i];
			Channel::iterator	chan_it = _channel_book.find(channel_name);

			if (chan_it == _channel_book.end()){ // channel does not exists
				if (channel_name.size() > 50){
					msg = ERR_BADCHANNAME(channel_name);
					send(client->get_fd(), msg.c_str(), msg.size(), 0);
					return 479; // errcode should be different than 0
				}
				Channel	*new_channel = new Channel(channel_name);
				// add channel to book
				_channel_book.insert(Channel::pair(channel_name, new_channel));
				client->join_channel(new_channel); // add channel to client's joined_channel and client to channel's members
				new_channel->set_operator(client);
				return _send_channel_update(new_channel, client, MSG_JOIN(channel_name, client->get_nickname()));				
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
				return _send_channel_update(channel, client, MSG_JOIN(channel_name, client->get_nickname()));
			}
		}
	}
	
	// }
	// send  bimbadaboumboum (~bimbadabo@freenode/user/bimbadaboumboum) a rejoint #freenode 
	// send RPL_TOPIC  ou RPL_NOTOPIC
	// send RPL_NAMREPLY
	// send RPL_ENDOFNAMES

	return SUCCESS;
}