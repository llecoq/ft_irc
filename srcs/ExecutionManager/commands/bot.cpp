#include "ExecutionManager.hpp"

int ExecutionManager::bot(Client *client, token_vector tokens) {
	if (tokens.size() != 3)
		return FAILED;
	if (tokens[1] == "bot" || tokens[2] == ":motdepassecomplique") {
		client->set_username("Claptrap");
		client->set_username("bot");
		client->set_password("AUTHENTIFICATION");
		client->set_authentication("AUTHENTICATION", "AUTHENTICATION");
		_send_rpl(client, RPL_WELCOME(tokens[1]), 001);
	}
	return SUCCESS;
}