#include "ExecutionManager.hpp"

int ExecutionManager::bot(Client *client, token_vector tokens) {
	if (tokens.size() != 3)
		return FAILED;
	if (tokens[1] == "bot" || tokens[2] == ":motdepassecomplique") {
		std::string	bot("bot");

		_bot_fd = client->get_fd();
		init_client(_bot_fd, bot.c_str());
		client->set_username("Claptrap");
		client->set_nickname("bot");
		client->set_password("AUTHENTICATION");
		client->set_authentication("AUTHENTICATION", "AUTHENTICATION");
		_send_rpl(client, RPL_WELCOME(tokens[1]), 001); // autre message
	}
	return SUCCESS;
}