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
	if (channel_topic.empty() == 0)
		msg = RPL_NOTOPIC(client_nickname, channel_name);
	else
		msg = RPL_TOPIC(client_nickname, channel_name, channel_topic);
	send(client->get_fd(), msg.c_str(), msg.size(), 0);

	msg = RPL_NAMREPLY(channel_name, client_nickname);
	send(client->get_fd(), msg.c_str(), msg.size(), 0);

	msg = RPL_ENDOFNAMES(channel_name, client_nickname);
	send(client->get_fd(), msg.c_str(), msg.size(), 0);
	

	// send RPL_NAMREPLY
	// send RPL_ENDOFNAMES
	return 0;
}