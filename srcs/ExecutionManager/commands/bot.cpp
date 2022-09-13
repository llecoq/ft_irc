#include "ExecutionManager.hpp"

int ExecutionManager::bot(Client *client, token_vector tokens) {
	if (tokens.size() != 3)
		return FAILED;
	if (tokens[1] == "bot" || tokens[2] == ":motdepassecomplique") {
		_bot_fd = client->get_fd();
		client->set_username("Claptrap");
		client->set_nickname("bot");
		client->set_password("AUTHENTICATION");
		client->set_authentication("AUTHENTICATION", "AUTHENTICATION");
		if (client->get_authentication() == false)
			std::cout << "MAIS" << std::endl;
		_send_rpl(client, RPL_WELCOME(tokens[1]), 001);
	}
	return SUCCESS;
}