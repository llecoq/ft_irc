#include "ExecutionManager.hpp"

int ExecutionManager::kill(Client *client, token_vector tokens) {
	std::string	cmd("KILL");
	std::string	msg;

	if (client->get_fd() != _bot_fd)
		return _send_rpl(client, ERR_NOPRIVILEGES, 481);
	if (tokens.size() < 3)
		return _send_rpl(client, ERR_NEEDMOREPARAMS(cmd), 461);
	msg = MSG_KILL(tokens[1], tokens[2]);
	send(_find_fd_client_by_name(tokens[1]), msg.c_str(), msg.size(), 0);
	close(_find_fd_client_by_name(tokens[1]));
	return SUCCESS;
}