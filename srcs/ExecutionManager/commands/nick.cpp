#include "ExecutionManager.hpp"

std::string ExecutionManager::nick(Client *client, token_vector tokens) {
	(void)client;
	(void)tokens;
	return "Bijour from nick";
}