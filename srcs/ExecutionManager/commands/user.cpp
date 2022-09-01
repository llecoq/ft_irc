#include "ExecutionManager.hpp"

unsigned int ExecutionManager::user(Client *client, token_vector tokens) {
	std::string	cmd("USER");
	std::string	msg;
	
	if (tokens.size() < 5) {
		msg = ERR_NEEDMOREPARAMS(cmd);
		send(client->get_fd(), msg.c_str(), msg.size(), 0);
		return 461;
	}
	if (client->get_authentication() == true) {
		send(client->get_fd(), ERR_ALREADYREGISTRED, sizeof ERR_ALREADYREGISTRED, 0);
		return 462;
	}
	client->set_username(tokens[1]);
	client->set_realname(tokens[4]); // attention ':' included
	if (client->get_nickname().empty() == 0
		&& client->get_username().empty() == 0
		&& client->get_password().empty() == 0)
		client->set_authentication(_password, client->get_password());
	if (client->get_authentication() == true){
		msg = RPL_WELCOME(client->get_nickname());
		send(client->get_fd(), msg.c_str(), msg.size(), 0);
	}
	return SUCCESS;
}