#include "ExecutionManager.hpp"

//KICK <channel> <client> :[<message>]
//ATTENTION there can be several channels / clients and in that case there CANNOT be a kick message
//soit 
	//KICK <channel> <client>,<client>,<client>,<client>
//soit 3 channels->3 users
	//KICK <channel>,<channel>,<channel> <client>,<client>,<client>
int ExecutionManager::kick(Client *client, token_vector tokens) {
	std::string	cmd("KICK");

	if (client->get_authentication() == false)
		return _send_rpl(client, ERR_NOTREGISTERED, 451);
	if (tokens.size() < 3)
		return _send_rpl(client, ERR_NEEDMOREPARAMS(cmd), 461);

	//========
	//On weechat, chan always exist bc command kick can only be done IN a channel
	Channel::iterator chan_iterator = _channel_book.find(tokens[1]);
	if (chan_iterator == _channel_book.end())
		return _send_rpl(client, ERR_NOSUCHCHANNEL(tokens[1]), 403);
	Channel *channel = chan_iterator->second;
	if (channel->user_is_in_channel(client) == false)
		return (_send_rpl(client, ERR_NOTONCHANNEL(channel->get_name()), 442));
	//========

	//NEED MODE to test those -> try on freenode
	if (channel->get_operator() != client)
		return (_send_rpl(client, ERR_CHANOPRIVSNEEDED(channel->get_name()), 482));
	if (channel->user_is_in_channel_by_name(tokens[2]) == false)
		return (_send_rpl(client, ERR_USERNOTINCHANNEL(tokens[2],channel->get_name()), 441));
	//if I am kicking myself --> NO


	// [<message>]
	//CLIENT IS in channel and is operator AND target is in the channel so now kick him out
	//USE PART COMMAND
	//Remove target from channel._members
	//Remove channel from client._joined_channels

	//SEND broadcast msg to the entire channel to let them now target has been kicked
	//send msg to target to let him know he has been kicked

	return SUCCESS;
}
/*
ERR_CHANOPRIVSNEEDED
ERR_NEEDMOREPARAMS
ERR_NOTONCHANNEL
ERR_USERNOTINCHANNEL          

Not for us :
	ERR_BADCHANMASK
*/