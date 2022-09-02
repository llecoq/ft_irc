#include "ExecutionManager.hpp"

unsigned int ExecutionManager::nick(Client *client, token_vector tokens) {
	std::string	cmd("NICK");

	if (tokens.size() < 2){
		return _send_rpl(client, ERR_NEEDMOREPARAMS(cmd), 461);
	}
	client->set_nickname(tokens[1]);
	client->set_authentication(_password, client->get_password());
	if (client->get_authentication() == true){
		_send_rpl(client, RPL_WELCOME(client->get_nickname()), 001);
	}
	return SUCCESS;
}