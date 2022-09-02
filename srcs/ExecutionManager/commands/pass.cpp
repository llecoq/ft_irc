#include "ExecutionManager.hpp"

unsigned int ExecutionManager::pass(Client *client, token_vector tokens) {
	std::string	cmd("PASS");

	if (tokens.size() < 2){
		return _send_rpl(client, ERR_NEEDMOREPARAMS(cmd), 461);
	}
	if (client->get_authentication() == true) {
		return _send_rpl(client, ERR_ALREADYREGISTRED, 462);
	}
	client->set_password(tokens[1]);
	return SUCCESS;
}