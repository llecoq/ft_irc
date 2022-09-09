#include "ExecutionManager.hpp"

//KICK <channel> <client> :[<message>]
//Only ONE channel but multiple client is ok and client parameter is ALWAYS parsed 
	//KICK #lalala abonnel,,,,, WORKS bc remove ","

int ExecutionManager::_kick_errors(Client *client, token_vector tokens, Channel *channel) {
	std::string	cmd("KICK");

	if (client->get_authentication() == false)
		return _send_rpl(client, ERR_NOTREGISTERED, 451);
	if (tokens.size() < 3)
		return _send_rpl(client, ERR_NEEDMOREPARAMS(cmd), 461);

	//NEED MODE to test those -> try on freenode
	if (channel->get_operator() != client)
		return (_send_rpl(client, ERR_CHANOPRIVSNEEDED(channel->get_name()), 482));
	return (SUCCESS);
}


int ExecutionManager::kick(Client *client, token_vector tokens) {
	Channel::iterator chan_iterator = _channel_book.find(tokens[1]);
	Channel *channel = NULL;
	if (chan_iterator != _channel_book.end())
		channel = chan_iterator->second;

	if (int error = _kick_errors(client, tokens, channel))
		return (error);

	//KICK #channel user1,user2 -> user1 does not exist, user2 will still be kicked so
	//NO RETURN inside for loop except if operator kicks himself first
	token_vector targets = _split(tokens[2], ",");
	for (token_iterator it = targets.begin(); it != targets.end(); it++) {
		//On weechat, chan always exist bc command kick can only be done IN a channel
		chan_iterator = _channel_book.find(tokens[1]);
		if (chan_iterator == _channel_book.end())
			return _send_rpl(client, ERR_NOSUCHCHANNEL(tokens[1]), 403);
		//OK to kick myself BUT if kicking myself first THEN STOPS
		if (channel->user_is_in_channel(client) == false)
			return (_send_rpl(client, ERR_NOTONCHANNEL(channel->get_name()), 442));

		Client *target_client = _get_client_by_name(*it);
		if (channel->user_is_in_channel(target_client) == false) {
			_send_rpl(client, ERR_USERNOTINCHANNEL(tokens[2],channel->get_name()), 441);
			continue;
		}
	
		std::string kick_msg = ((tokens.size() < 4) ? client->get_nickname() : tokens[3]);
		target_client->leave_channel(channel->get_name(), kick_msg, KICK);
		_remove_empty_channel(chan_iterator);
		//When kicking someone, they are still in the list of members on the right of the channel
		//problem with the KICK msg, lolo has kicked abonnel when it should be the other way around
	}
	return SUCCESS;
}
		//tester KICK_MSG
		//SEND broadcast msg to the entire channel to let them now target has been kicked
		//ex : airano has kicked abonnel (airano)
		//:WiZ KICK #Finnish John --> VOIR MSG_ dans numeric_replies
		//Avec comment : airano has kicked abonnel (t trop une merde)
		//from the kicking user : :airano!~arianus@freenode-ts4.94b.uj4jb0.IP KICK #chaninu abonnel :t trop une merde
		//send msg to target to let him know he has been kicked

/*
ERR_CHANOPRIVSNEEDED
ERR_NEEDMOREPARAMS
ERR_NOTONCHANNEL
ERR_USERNOTINCHANNEL          

Not for us :
	ERR_BADCHANMASK
*/