#include "ExecutionManager.hpp"

unsigned int ExecutionManager::nick(Client *client, token_vector tokens) {
	std::string	cmd("NICK");
	std::string	msg;
	
	if (tokens.size() < 2){
		msg = ERR_NEEDMOREPARAMS(cmd);
		send(client->get_fd(), msg.c_str(), msg.size(), 0);
		return 461;
	}
	client->set_nickname(tokens[1]);
	return SUCCESS;
}