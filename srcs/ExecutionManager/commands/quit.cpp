#include "ExecutionManager.hpp"

int ExecutionManager::quit(Client *client, token_vector tokens) {
	std::string		cmd("QUIT");
	std::string		msg(client->get_nickname());
	token_vector	empty_channels;


	if (tokens.size() > 1)
		msg = tokens[1];
	empty_channels = client->leave_joined_channels(msg, QUIT);
	for (size_t i = 0; i < empty_channels.size(); i++)
		_remove_empty_channel(_channel_book.find(empty_channels[i]));
	_client_book.erase(client->get_fd());
	delete client;
	return SUCCESS;
}