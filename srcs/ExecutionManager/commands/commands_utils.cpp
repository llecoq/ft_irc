#include "ExecutionManager.hpp"

int	ExecutionManager::_send_channel_update(Channel *channel, Client *client, std::string msg)
{
	std::string	channel_name = channel->get_name();
	std::string	channel_topic = channel->get_topic();
	std::string	client_nickname = client->get_nickname();
	// channel->broadcast(NULL, msg); // NULL => send to EVERYONE
	// send  bimbadaboumboum (~bimbadabo@freenode/user/bimbadaboumboum) a rejoint #freenode 
	
	// :llecoq!~llecoq@127.0.0.1 JOIN #baba
	channel->broadcast(NULL, msg);
	if (channel_topic.empty() == 1)
		_send_rpl(client, RPL_NOTOPIC(client_nickname, channel_name), 331);
	else
		_send_rpl(client, RPL_TOPIC(client_nickname, channel_name, channel_topic), 332);
	_send_rpl(client, RPL_NAMREPLY(channel_name, client_nickname), 353);
	_send_rpl(client, RPL_ENDOFNAMES(channel_name, client_nickname), 366);
	return SUCCESS;
}

int	ExecutionManager::_send_rpl(Client *client, std::string msg, int numeric)
{
	send(client->get_fd(), msg.c_str(), msg.size(), 0);
	return numeric;
}