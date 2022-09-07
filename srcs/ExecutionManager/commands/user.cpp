#include "ExecutionManager.hpp"

// on est cense pouvoir set un user avec ses params : USER t t t t
int ExecutionManager::user(Client *client, token_vector tokens) {
	std::string	cmd("USER");

	if (tokens.size() < 5){
		return _send_rpl(client, ERR_NEEDMOREPARAMS(cmd), 461);
	}
	if (client->get_authentication() == true) {
		return _send_rpl(client, ERR_ALREADYREGISTRED, 462);
	}
	client->set_username(tokens[1]);
	client->set_realname(tokens[4]); // attention ':' included
	client->set_authentication(_password, client->get_password());
	if (client->get_authentication() == true){
		_send_rpl(client, RPL_WELCOME(client->get_nickname()), 001);
		// upon successful registration, send:
			// - welcome msg
			// - basic informations about server
			// - basic help or cmds like join #channel 
			// - user mode 
	}
	return SUCCESS;
}