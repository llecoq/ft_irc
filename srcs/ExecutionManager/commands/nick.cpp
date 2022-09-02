#include "ExecutionManager.hpp"

unsigned int ExecutionManager::nick(Client *client, token_vector tokens) {
	std::string	cmd("NICK");
	std::string	msg;
	
	if (tokens.size() < 2){
		msg = ERR_NEEDMOREPARAMS(cmd);
		send(client->get_fd(), msg.c_str(), msg.size(), 0);
		return 461;
	}
	//check if nickname syntax is authorized (for ex. can't start or can't have # in it
	// so user and channel will never be the same)
	client->set_nickname(tokens[1]);
	client->set_authentication(_password, client->get_password());
	if (client->get_authentication() == true){
		msg = RPL_WELCOME(client->get_nickname());
		send(client->get_fd(), msg.c_str(), msg.size(), 0);
	}
	return SUCCESS;
}