#include "ExecutionManager.hpp"

int ExecutionManager::quit(Client *client, token_vector tokens) {
	std::string	cmd("QUIT");
	std::string	msg(client->get_nickname());

	if (tokens.size() > 1)
		msg = tokens[1];
	client->leave_joined_channels(msg);
	// remove empty channels
	return SUCCESS;
}