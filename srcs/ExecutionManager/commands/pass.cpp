#include "ExecutionManager.hpp"

unsigned int ExecutionManager::pass(Client *client, token_vector tokens) {
	std::string	cmd("PASS");
	std::string	msg;
	
	if (tokens.size() < 2){
		msg = ERR_NEEDMOREPARAMS(cmd);
		send(client->get_fd(), msg.c_str(), msg.size(), 0);
		return 461;
	}
	if (client->get_authentication() == true) {
		send(client->get_fd(), ERR_ALREADYREGISTRED, sizeof ERR_ALREADYREGISTRED, 0);
		return 462;
	}
	client->set_password(tokens[1]);
	return SUCCESS;
}